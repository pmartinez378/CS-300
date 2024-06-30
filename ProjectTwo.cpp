//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Pedro Martinez
// Version     : 1.0
// Copyright   : Copyright © 2023 SNHU COCE
// Description : Project Two
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

// Define the Course class
class Course {
public:
    std::string courseNumber;
    std::string title;
    std::vector<std::string> prerequisites;
    std::string instructor;
    int credits;

    Course(std::string number, std::string title, std::string instructor, int credits)
        : courseNumber(number), title(title), instructor(instructor), credits(credits) {}
};

// Function declarations
std::map<std::string, Course> loadCourses(const std::string& fileName);
void printCourseList(const std::map<std::string, Course>& courses);
void printCourseDetails(const std::map<std::string, Course>& courses, const std::string& courseNumber);

int main() {
    std::map<std::string, Course> courses;
    int option = 0;
    std::string input;

    while (option != 9) {
        std::cout << "Menu:\n";
        std::cout << "1. Load course data\n";
        std::cout << "2. Print course list\n";
        std::cout << "3. Print course details\n";
        std::cout << "9. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> input;
        
        try {
            option = std::stoi(input);
        } catch (std::invalid_argument& e) {
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (option) {
            case 1: {
                std::string fileName;
                std::cout << "Enter file name: ";
                std::cin >> fileName;
                courses = loadCourses(fileName);
                break;
            }
            case 2:
                printCourseList(courses);
                break;
            case 3: {
                std::string courseNumber;
                std::cout << "Enter course number: ";
                std::cin >> courseNumber;
                printCourseDetails(courses, courseNumber);
                break;
            }
            case 9:
                std::cout << "Thank you for using the course planner!\n";
                break;
            default:
                std::cout << option << " is not a valid option.\n";
                break;
        }
    }

    return 0;
}

std::map<std::string, Course> loadCourses(const std::string& fileName) {
    std::map<std::string, Course> courses;
    std::ifstream file(fileName);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << fileName << "\n";
        return courses;
    }

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string number, title, instructor, credits_str, prerequisite;
        int credits;

        getline(ss, number, ',');
        getline(ss, title, ',');
        getline(ss, instructor, ',');
        getline(ss, credits_str, ',');
        credits = std::stoi(credits_str);

        Course course(number, title, instructor, credits);
        while (getline(ss, prerequisite, ',')) {
            course.prerequisites.push_back(prerequisite);
        }

        courses[number] = course;
    }

    file.close();
    std::cout << "Loaded " << courses.size() << " courses from " << fileName << "\n";
    return courses;
}

void printCourseList(const std::map<std::string, Course>& courses) {
    if (courses.empty()) {
        std::cout << "No courses loaded. Please load a course file first.\n";
        return;
    }

    std::vector<std::string> courseNumbers;
    for (const auto& pair : courses) {
        courseNumbers.push_back(pair.first);
    }

    std::sort(courseNumbers.begin(), courseNumbers.end());

    std::cout << "Here is a sample schedule:\n";
    for (const auto& number : courseNumbers) {
        const Course& course = courses.at(number);
        std::cout << number << ", " << course.title << ", Instructor: " << course.instructor << ", Credits: " << course.credits << "\n";
    }
}

void printCourseDetails(const std::map<std::string, Course>& courses, const std::string& courseNumber) {
    if (courses.find(courseNumber) == courses.end()) {
        std::cout << "Course not found\n";
        return;
    }

    const Course& course = courses.at(courseNumber);
    std::cout << "Course: " << course.courseNumber << ", " << course.title << "\n";
    std::cout << "Instructor: " << course.instructor << "\n";
    std::cout << "Credits: " << course.credits << "\n";
    std::cout << "Prerequisites: ";
    
    for (size_t i = 0; i < course.prerequisites.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << course.prerequisites[i];
    }
    std::cout << "\n";
}

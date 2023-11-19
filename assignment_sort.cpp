#include <iostream>
#include <queue>
#include <vector>
#include <ctime>
#include <iomanip>
#include <stdexcept>
#include <cctype>

using namespace std;

struct Assignment {
    string name;
    string subject;
    string dueDate;
    int dueHour;
    int dueMinute;
    int estimatedHours;
};

struct CompareAssignments {
    bool operator()(const Assignment& a1, const Assignment& a2) const {
        return a1.dueDate > a2.dueDate;
    }
};

void displayAssignment(const Assignment& assignment, int remainingDays, int remainingHours, int remainingMinutes) {
    cout << setw(15) << left << assignment.subject
         << setw(15) << left << assignment.dueDate
         << setw(1) << left << setfill(' ') << assignment.dueHour 
		 << setw(1) << left << ":" 
		 << setw(8) << left << setfill(' ')<< assignment.dueMinute 
         << setw(5) << left << assignment.estimatedHours
         << setw(1) << left << remainingDays << " days " << remainingHours << " hours " << remainingMinutes << " minutes." << endl;
}

void organizeHomeworkAssignments(vector<Assignment>& assignments, vector<int>& schedule) {
    priority_queue<Assignment, vector<Assignment>, CompareAssignments> assignmentQueue;

    for (size_t i = 0; i < assignments.size(); ++i) {
        Assignment& assignment = assignments[i];
        cout << "Enter subject for assignment " << i + 1 << ": ";
        cin >> assignment.subject;

        cout << "Enter due date for assignment " << i + 1 << " (YYYY-MM-DD): ";
        cin >> assignment.dueDate;

        cout << "Enter due hour for assignment " << i + 1 << ": ";
        cin >> assignment.dueHour;

        cout << "Enter due minute for assignment " << i + 1 << ": ";
        cin >> assignment.dueMinute;

        cout << "Enter estimated hours for assignment " << i + 1 << ": ";
        cin >> assignment.estimatedHours;

        assignmentQueue.push(assignment);
    }

    time_t currentTime = time(0);
    tm* now = localtime(&currentTime);

    cout << setfill('-') << setw(80) << "-" << setfill(' ') << endl;
    cout << setw(15) << left << "Subject" << setw(15) << left << "Due Date" << setw(10) << left << "Due Time"
         << setw(10) << left << "Est. Hours" << setw(20) << left << "Remaining Time" << endl;
    cout << setfill('-') << setw(80) << "-" << setfill(' ') << endl;

    while (!assignmentQueue.empty()) {
        Assignment currentAssignment = assignmentQueue.top();
        assignmentQueue.pop();

        tm dueTime = *now;
        sscanf(currentAssignment.dueDate.c_str(), "%d-%d-%d", &dueTime.tm_year, &dueTime.tm_mon, &dueTime.tm_mday);
        dueTime.tm_year -= 1900;
        dueTime.tm_mon -= 1;
        dueTime.tm_hour = currentAssignment.dueHour;
        dueTime.tm_min = currentAssignment.dueMinute;

        time_t dueTimestamp = mktime(&dueTime);
        double remainingTimeSeconds = difftime(dueTimestamp, currentTime);

        int remainingDays = static_cast<int>(remainingTimeSeconds / (3600 * 24));
        int remainingHours = static_cast<int>((remainingTimeSeconds - remainingDays * 3600 * 24) / 3600);
        int remainingMinutes = static_cast<int>((remainingTimeSeconds - remainingDays * 3600 * 24 - remainingHours * 3600) / 60);

        bool scheduled = false;
        for (size_t i = 0; i < schedule.size(); ++i) {
            int& timeSlot = schedule[i];
            if (timeSlot >= currentAssignment.estimatedHours) {
                timeSlot -= currentAssignment.estimatedHours;
                scheduled = true;

                displayAssignment(currentAssignment, remainingDays, remainingHours, remainingMinutes);

                break;
            }
        }

        if (!scheduled) {
            displayAssignment(currentAssignment, remainingDays, remainingHours, remainingMinutes);
        }
    }

    cout << setfill('-') << setw(80) << "-" << setfill(' ') << endl;
}

int main() {
    int numAssignments;

    cout << "Enter the number of assignments: ";
    cin >> numAssignments;

    vector<int> schedule(numAssignments, 8);

    vector<Assignment> assignments(numAssignments);
    organizeHomeworkAssignments(assignments, schedule);

    return 0;
}


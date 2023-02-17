// === Region: Project Overview ===
// 
// Here is the skelton code of COMP2011 PA3
//
// Project TA: CHUNG, Peter (cspeter@cse.ust.hk)
// All input/output handlings are done in the skeleton code
// You do not need to cin/cout anything in your extra code!
//
// For code-level questions, please send a direct email to the above TA. 
// Asking questions with code in a discussion forum (e.g., Piazza) may cause plagiarism issues
// Usually, you will get the quickest response via a direct email.
//
// Assumptions:
// The course code is the unique key (i.e., there won't be duplicated course codes in the system). 
// This assumption is necessary for many operations (e.g., searching, insertions, and deletions, etc.)
//
// ================================= 

#include <iostream>
#include <cstring>
using namespace std;

// === Region: constants and structs ===
// The constants are structs are defined in this region
// ===================================

// constants
const int MAX_CODE = 10; // at most 10 characters (including the NULL character)
const int MAX_TITLE = 100; // at most 100 characters (including the NULL character)
struct CourseItem; // needed because Course needs to refer to CourseItem*
// A sorted linked list of Course. List items are sorted by the course code
struct Course {
    char code[MAX_CODE];        // course code
    char title[MAX_TITLE];      // course title
    int credit;                 // course credit
    Course* next;               // a pointer pointing to the next Course
    CourseItem* exclusions;     // a sorted linked list of CourseItem
    CourseItem* prerequisites;  // a sorted linked list of CourseItem
};
// A sorted linked list of CourseItem. List items are sorted by course->code
struct CourseItem {
    Course *course;             // pointing to the course
    CourseItem *next;           // a pointer pointing to the next CourseItem
};

// === Region: function declarations ===
// The function declarations. 
//
// If needed, you can add your own helper functions
//
// The implementation is done in the function definitions after the main() function
// ===================================


/**
 * function ll_print_all prints the linked lists stored in the system
 * @param head pointing to the head of the linked list
*/
void ll_print_all(const Course* head); // given, you cannot make any changes

/**
 * function ll_insert_prerequisite inserts a pre-requisite
 * Example: if COMP2011 requires COMP1022P, the targetCode is COMP2011 and the preCode is COMP1022P
 * @param head pointing to the head of the linked list
 * @param targetCode stores the course code of the target
 * @param preCode stores the course code of the pre-requisite 
 * @return true if the insertion is complete. false otherwise
*/
bool ll_insert_prerequisite(Course* head, const char targetCode[MAX_CODE], const char preCode[MAX_CODE]);

/**
 * function ll_insert_exclusion inserts an exclusion
 * Example: if COMP2011 excludes COMP1022P, the targetCode is COMP2011 and the excludeCode is COMP1022P
 * @param head pointing to the head of the linked list
 * @param targetCode stores the course code of the target
 * @param excludeCode stores the course code to be excluded
 * @return true if the insertion is complete. false otherwise 
*/
bool ll_insert_exclusion(Course* head, const char targetCode[MAX_CODE], const char excludeCode[MAX_CODE]);

/**
 * function ll_delete_prerequisite deletes a pre-requisite
 * Example: Given the input, if there is a pre-requisite, the pre-requisite will be deleted
 * @param head pointing to the head of the linked list
 * @param targetCode stores the course code of the target
 * @param preCode stores the course code of pre-requisite
 * @return true if the deletion is complete. false otherwise
*/
bool ll_delete_prerequisite(Course* head, const char targetCode[MAX_CODE], const char preCode[MAX_CODE]);

/**
 * function ll_delete_exclusion deletes an exclusion
 * Example: Given the input, if there is an exclusion, the exclusion will be deleted
 * @param head pointing to the head of the linked list
 * @param targetCode stores the course code of the target
 * @param excludeCode stores the course code of exclusion
 * @return true if the deletion is complete. false otherwise 
*/
bool ll_delete_exclusion(Course* head, const char targetCode[MAX_CODE], const char excludeCode[MAX_CODE]);

/**
 * function ll_insert_course inserts a course
 * Note: head is passed by reference because head may be changed during the insertion
 * @param head pointing to the head of the linked list
 * @param c is the course code 
 * @param t is the course title
 * @param cred is the course credit
 * @return true if the insertion is complete. false otherwise
*/
bool ll_insert_course(Course* &head, const char c[MAX_CODE], const char t[MAX_TITLE], int cred);

/**
 * function ll_delete_course deletes an existing course
 * Note: head is passed by reference because head may be changed during the deletion
 * @param head pointing to the head of the linked list
 * @param c is the course code
 * @return true if the deletion is complete. false otherwise
*/
bool ll_delete_course(Course* &head, const char c[MAX_CODE]);

/**
 * function ll_modify_course_title modifies the course title attribute of a course
 * @param head pointing to the head of the linked list
 * @param c is the course code
 * @param t is the new course title
 * @return true if the modification is complete. false otherwise 
*/
bool ll_modify_course_title(Course* head, const char c[MAX_CODE], const char t[MAX_TITLE]);

/**
 * function ll_modify_course_credit modifies the course credit attribute of a course
 * @param head pointing to the head of the linked list
 * @param c is the course code
 * @param cred is the new credit
 * @return true if the modification is complete. false otherwise
*/
bool ll_modify_course_credit(Course* head, const char c[MAX_CODE], int cred);



/**
 * function ll_cleanup_all cleans up the linked lists used in the system. It restores the original states (i.e., empty linked lists) of the system. 
 * No memory leak should be found after the clean up
 * Note: head is passed by reference because head may be changed during the clean up
 * @param head pointing to the head of the linked list
*/
void ll_cleanup_all(Course* &head);

// === Region: The main() function ===
// The main function is given
// DO NOT MODIFY anything inside the main() function
// ===================================

/**
 * function enter_credit: A helper function to enter a valid credit
 * ensure the credit is a non-negative integer
*/
int enter_credit() {
    int credit;
    while (true) {
        cout << "Enter the credit: " ;
        cin >> credit;
        if ( credit >= 0 )
            return credit;
        cout << "Invalid credit: " << credit << endl;
    }
}

/**
 * function main - the main function
*/
int main() {
    Course *clist = nullptr;
    enum MeunOption {
        OPTION_DISPLAY_CURRENT_LIST = 0,
        OPTION_INSERT_COURSE,
        OPTION_INSERT_PRE_REQUISITE,
        OPTION_INSERT_EXCLUSION,
        OPTION_DELETE_COURSE,
        OPTION_DELETE_PRE_REQUISITE,
        OPTION_DELETE_EXCLUSION,
        OPTION_MODIFY_COURSE_TITLE,
        OPTION_MODIFY_COURSE_CREDIT,
        OPTION_EXIT_WITHOUT_CLEANUP,
        OPTION_EXIT_WITH_CLEANUP, 
        MAX_MENU_OPTIONS
    };
    const int MAX_MENU_OPTIONS_LENGTH = 50;
    char menuOptions[MAX_MENU_OPTIONS][MAX_MENU_OPTIONS_LENGTH] = {
        "Display the current list",
        "Insert a new course",
        "Insert a pre-requisite",
        "Insert an exclusion",
        "Delete an existing course",
        "Delete an existing pre-requisite",
        "Delete an existing exclusion",
        "Modify a course title",
        "Modify a course credit",
        "Exit without clean up",
        "Exit with clean up"
    };
    
    int option = 0;
    int i = 0;
    int credit = 0;
    // It is tricky to check the input character array, write assumptions that we don't need to check
    char code[MAX_CODE] = ""; 
    char title[MAX_TITLE] = "" ;
    char targetCode[MAX_CODE] = "";
   
    bool ret = false;
    
    while (true) {
        cout << "=== Menu ===" << endl;
        for (i=0; i<MAX_MENU_OPTIONS; i++) 
            cout << i+1 << ": " << menuOptions[i] << endl; // shift by +1 when display

        cout << "Enter your option: ";
        cin >> option;

        option = option - 1; // shift by -1 after entering the option

        // The invalid menu option handling
        if ( option < 0 || option >= MAX_MENU_OPTIONS ) {
            cout << "Invalid option" << endl;
            continue;
        }

        // Exit operations handling
        if (option == OPTION_EXIT_WITHOUT_CLEANUP)
            break; // break the while loop
        else if (option == OPTION_EXIT_WITH_CLEANUP) {
            cout << "=== Cleanup ===" << endl;
            ll_cleanup_all(clist);
            ll_print_all(clist);
            break; //  break the while loop
        }
        
        switch (option) {
            case OPTION_DISPLAY_CURRENT_LIST:
                ll_print_all(clist);
                break;
            case OPTION_INSERT_COURSE:
                cout << "Enter a course code: ";
                cin >> code;
                cout << "Enter a course title: ";
                cin.ignore(); // necessary when mixing cin>> and cin.getline
                cin.getline(title, MAX_TITLE);
                credit = enter_credit();
                ret = ll_insert_course(clist, code, title, credit);
                if ( ret == false ) {
                     cout << "Failed to insert " << code << endl ;
                }
                else {
                    cout << code << " is successfully inserted" << endl ;
                    ll_print_all(clist);
                }
                break;
            case OPTION_INSERT_PRE_REQUISITE:
                cout << "Enter the target course code: ";
                cin >> targetCode;
                cout << "Enter the pre-requisite course code: ";
                cin >> code;
                if ( strcmp(targetCode, code) == 0) {
                    cout << "Cannot insert a pre-requisite to the same course " << code << endl;
                } else {
                    ret = ll_insert_prerequisite(clist, targetCode, code);
                    if ( ret == false ) {
                        cout << "Failed to insert pre-requisite " << targetCode << ", " << code << endl;
                    } else {
                        cout << "Inserted a pre-requisite " << targetCode << ", " << code << endl;
                        ll_print_all(clist);
                    }
                }
                break;
            case OPTION_INSERT_EXCLUSION:
                cout << "Enter the target course code: ";
                cin >> targetCode;
                cout << "Enter the exclusion course code: ";
                cin >> code;
                if ( strcmp(targetCode, code) == 0) {
                    cout << "Cannot insert an exclusion to the same course " << code << endl;
                } else {
                    ret = ll_insert_exclusion(clist, targetCode, code);
                    if ( ret == false ) {
                        cout << "Failed to insert exclusion " << targetCode << ", " << code << endl;
                    } else {
                        cout << "Inserted an exclusion " << targetCode << ", " << code << endl;
                        ll_print_all(clist);
                    }
                }
                break;
            case OPTION_DELETE_COURSE:
                cout << "Enter the course code: ";
                cin >> code ;
                ret = ll_delete_course(clist, code);
                if ( ret == false ) {
                    cout << "Failed to delete course " << code << endl;
                } else {
                    cout << "Deleted a course " << code << endl ;
                    ll_print_all(clist);
                }
                break;
            case OPTION_DELETE_PRE_REQUISITE:
                 cout << "Enter the target course code: ";
                cin >> targetCode;
                cout << "Enter the pre-requisite course code: ";
                cin >> code;
                ret = ll_delete_prerequisite(clist, targetCode, code);
                if ( ret == false ) {
                    cout << "Failed to delete pre-requisite " << targetCode << ", " << code << endl;
                } else {
                    cout << "Deleted a pre-requisite " << targetCode << ", " << code << endl;
                    ll_print_all(clist);
                }
                break;
            case OPTION_DELETE_EXCLUSION:
                cout << "Enter the target course code: ";
                cin >> targetCode;
                cout << "Enter the pre-requisite course code: ";
                cin >> code;
                ret = ll_delete_exclusion(clist, targetCode, code);
                if ( ret == false ) {
                    cout << "Failed to delete exclusion " << targetCode << ", " << code << endl;
                } else {
                    cout << "Deleted an exclusion " << targetCode << ", " << code << endl;
                    ll_print_all(clist);
                }
                break;
            case OPTION_MODIFY_COURSE_TITLE:
                cout << "Enter the course code: ";
                cin >> code;
                cout << "Enter the new course title: " ;
                cin.ignore();
                cin.getline(title, MAX_TITLE);
                ret = ll_modify_course_title(clist, code, title);
                if ( ret == false ) {
                    cout << "Failed to modify the course title of " << code << endl ;
                } else {
                    cout << "The course title of " << code << " is modified" << endl ;
                    ll_print_all(clist);
                }
                break;
            case OPTION_MODIFY_COURSE_CREDIT:
                cout << "Enter the course code: ";
                cin >> code ;
                credit = enter_credit();
                ret = ll_modify_course_credit(clist, code, credit);
                if ( ret == false ) {
                    cout << "Failed to modify the course credit of " << code << endl;
                } else {
                    cout << "The course credit of " << code << " is modified" << endl;
                    ll_print_all(clist);
                }
                break;
                
        } // end switch

    } // end while true
    return 0;
}


// === Region: function definitions ===
// You should implement the functions below
// ====================================


// This function is given
// DO NOT MODIFY THIS FUNCTION
// Otherwise, you may not be able to pass the ZINC test cases
void ll_print_all(const Course* head) {
    const Course *p;
    const CourseItem *q;
    int count;

    cout << "=== Course List (Code[Credits]) ===" << endl;
    count = 0;
    for (p = head; p!= nullptr; p = p->next) {
        cout << p->code << "[" << p->credit << "]" ;
        if ( p->next != nullptr )
            cout << " -> ";
        count++;
    }
    if ( count == 0 ) {
        cout << "No courses in the list";
    }
    cout << endl;

    cout << "=== Course titles ===" << endl ;
    count = 0;
    for (p = head; p!= nullptr; p = p->next) {
        cout << p->code << ": " << p->title << endl ;
        count++;
    }
    if ( count == 0 ) {
        cout << "No course titles" << endl;
    }

    cout << "=== Pre-requisites ===" << endl ;
    count = 0;
    for (p = head; p!= nullptr; p = p->next) {
        q = p->prerequisites;
        if ( q != nullptr ) {
            cout << p->code << ": ";
            for ( ; q != nullptr; q = q->next ) {
                cout << q->course->code ;
                if ( q->next != nullptr )
                    cout << ", " ;
            }
            count++;
            cout << endl;
        }
    }
    if ( count == 0 ) {
        cout << "No pre-requisites" << endl;
    }

    cout << "=== Exclusions ===" << endl ;
    count = 0;
    for (p = head; p!= nullptr; p = p->next) {
        q = p->exclusions;
        if ( q != nullptr ) {
            cout << p->code << ": ";
            for ( ; q != nullptr; q = q->next ) {
                cout << q->course->code ;
                if ( q->next != nullptr )
                    cout << ", " ;
            }
            count++;
            cout << endl;
        }
    }
    if ( count == 0 ) {
        cout << "No pre-exclusions" << endl;
    }

}



bool ll_insert_prerequisite(Course* head, const char targetCode[MAX_CODE], const char preCode[MAX_CODE]) {
    Course* p=head;
    CourseItem* newpre=new CourseItem;
    if(p==nullptr){
        delete newpre;
        return false;
    }
    for(Course* k=head;k!=nullptr;k=k->next){
        if(strcmp(k->code,preCode)==0){
            for(Course* q=head;q!=nullptr;q=q->next){
                
                if(strcmp(q->code,targetCode)==0){
                    newpre->course=k;
                    newpre->next=nullptr;    
                    if(q->prerequisites==nullptr){
                        q->prerequisites=newpre;
                        return true;
                    }else if(strcmp(q->prerequisites->course->code,preCode)>0){
                        CourseItem* temp=q->prerequisites;
                        q->prerequisites=newpre;
                        newpre->next=temp;
                        return true;
                    }
                    else{
                        CourseItem* j=q->prerequisites;
                        for(j;j!=nullptr;j=j->next){
                            if(strcmp(j->course->code,newpre->course->code)>0){
                                j=j->next;
                            }
                            else if(strcmp(j->course->code,newpre->course->code)==0){
                                delete newpre;
                                return false;
                            }
                            else{
                                newpre->next=j->next;
                                j->next=newpre;
                                return true;
                            }
                        }

                    }                   
                }
            }
        }
    }
    delete newpre;
    return false;
    // TODO: Implementation of inserting a pre-requisite
}
bool ll_insert_exclusion(Course* head, const char targetCode[MAX_CODE], const char excludeCode[MAX_CODE]) {
    Course* p=head;
    CourseItem* newexc=new CourseItem;
    if(p==nullptr){
        delete newexc;
        return false;
    }
    for(Course* k=head;k!=nullptr;k=k->next){
        if(strcmp(k->code,excludeCode)==0){
            for(Course* q=head;q!=nullptr;q=q->next){
                if(strcmp(q->code,targetCode)==0){
                    newexc->course=k;
                    newexc->next=nullptr;  
                    if(q->exclusions==nullptr){
                        q->exclusions=newexc;
                        return true;
                    }
                    else if(strcmp(q->exclusions->course->code,excludeCode)>0){
                        CourseItem* temp=q->exclusions;
                        q->exclusions=newexc;
                        newexc->next=temp;
                        return true;
                    }
                    else{
                        CourseItem* j=q->exclusions;
                        for(j;j!=nullptr;j=j->next){
                            if(strcmp(j->course->code,newexc->course->code)>0){
                                j=j->next;
                            }
                            else if(strcmp(j->course->code,newexc->course->code)==0){
                                delete newexc;
                                return false;
                            }
                            else{
                                newexc->next=j->next;
                                j->next=newexc;
                                return true;
                            }
                        }

                    }                   
                }
            }
        }
    }
    delete newexc;
    return false;
}

bool ll_delete_prerequisite(Course* head, const char targetCode[MAX_CODE], const char preCode[MAX_CODE]) {
    Course* p=head;
    if(strcmp(targetCode,preCode)==0){
        return false;
    }
    if(p==nullptr){
        return false;
    }
    for(Course* k=head;k!=nullptr;k=k->next){
        if(strcmp(k->code,preCode)==0){
            for(Course* q=head;q!=nullptr;q=q->next){          
                if(strcmp(q->code,targetCode)==0){
                    if(q->prerequisites==nullptr){ 
                        
                        return false;
                    }
                    else{ 
                        CourseItem*r=q->prerequisites;
                        for(r;r!=nullptr;r=r->next){
                            
                            if(r==q->prerequisites&&r->course==k&&r->next!=nullptr){
                                CourseItem* target=r->next; 
                                r->course=nullptr; 
                                q->prerequisites->course=target->course;
                                q->prerequisites->next=target->next;
                                delete target;
                                return true;
                            }
                            else if(r==q->prerequisites&&r->course==k&&r->next==nullptr){
                                q->prerequisites=nullptr;
                                return true;
                            }
                            else if(r->next->course==k){
                                CourseItem* temp=r;
                                CourseItem* target=r->next;  
                                temp->next=target->next;
                                target->course=nullptr;
                                delete target;
                                return true;
                            }
                        }
                        
                        

                    }                   
                }
            }
        }
    }
    
    return false;
}

bool ll_delete_exclusion(Course* head, const char targetCode[MAX_CODE], const char excludeCode[MAX_CODE]) {
    Course* p=head;
    if(strcmp(targetCode,excludeCode)==0){
        return false;
    }
    if(p==nullptr){
        return false;
    }
    for(Course* k=head;k!=nullptr;k=k->next){
        if(strcmp(k->code,excludeCode)==0){
            for(Course* q=head;q!=nullptr;q=q->next){          
                if(strcmp(q->code,targetCode)==0){
                    if(q->exclusions==nullptr){ 
                        
                        return false;
                    }
                    else{ 
                        CourseItem*r=q->exclusions;
                        for(r;r!=nullptr;r=r->next){
                            if(r==q->exclusions&&r->course==k&&r->next!=nullptr){
                                CourseItem* target=r->next; 
                                r->course=nullptr; 
                                q->exclusions->course=target->course;
                                q->exclusions->next=target->next;
                                delete target;
                                return true;
                            }
                            else if(r==q->exclusions&&r->course==k&&r->next==nullptr){
                                q->exclusions=nullptr;
                                return true;
                            }
                            else if(r->next->course==k){
                                CourseItem* temp=r;
                                CourseItem* target=r->next;
                                temp->next=target->next;
                                target->course=nullptr;
                                delete target;
                                return true;
                            }
                        }
                        
                        

                    }                   
                }
            }
        }
    }
    
    return false;
}




bool ll_insert_course(Course*& head, const char c[MAX_CODE], const char t[MAX_TITLE], int cred) {
    Course* newcourse = new Course;
    Course*p=head;
    strcpy(newcourse->code,c);
    strcpy(newcourse->title,t);
    newcourse->credit=cred;
    newcourse->exclusions=nullptr;
    newcourse->prerequisites=nullptr;
    newcourse->next=nullptr;
    if(p==nullptr){
        head=newcourse;
        return true;
        
    }
    else if(p==head&&strcmp(p->code,newcourse->code)>0){
        Course* temp=p;
        head=newcourse;
        newcourse->next=temp;
        temp=nullptr;
        return true;
    }
    while(p->next!=nullptr){
        if(strcmp(p->code,newcourse->code)>0){
            p=p->next;    
        }
        else if(strcmp(p->code,newcourse->code)==0){
            delete newcourse;
            return false;
        }
        else{
            newcourse->next=p->next;
            p->next=newcourse;
            return true;
        }
        
    }
    if(p->next==nullptr){
        p->next=newcourse;
        return true;
    }
    delete newcourse;
    return false;
    
}

bool ll_delete_course(Course*& head, const char c[MAX_CODE]) {

    // TODO: Implementation of deleting a course
    Course* k=head;
    for(k;k!=nullptr;k=k->next){
        bool i;
        bool j;
        if(strcmp(k->code,c)==0){
            Course* target=k;
            CourseItem* pre=target->prerequisites;
            CourseItem* exc=target->exclusions;
            while(pre!=nullptr){
                ll_delete_prerequisite(head,target->code,pre->course->code);
                pre=pre->next;
            }
            while(exc!=nullptr){
                ll_delete_exclusion(head,target->code,exc->course->code);
                exc=exc->next;
            }
            continue;
        }
        else{
            i=ll_delete_exclusion(head,k->code,c);
            j=ll_delete_prerequisite(head,k->code,c);
        }
        
    }
    Course*p=head;
    for(p;p!=nullptr;p=p->next){
        if (strcmp(p->code,c)==0&&p==head&&p->next!=nullptr)
        {  
            Course* newone=p->next;
            Course* temp=p;
            head=newone;
            temp=nullptr;
            delete temp;
            return true;
        }
        else if(strcmp(p->code,c)==0&&p==head&&p->next==nullptr){
            head=nullptr;
            return true;
        }
        
        else if(strcmp(p->next->code,c)==0){
            Course* previous=p;
            Course* current=p->next;
            previous->next=current->next;
            current=nullptr;
            delete current;
            return true;

        }

    }
    return false;
}

bool ll_modify_course_title(Course* head, const char c[MAX_CODE], const char t[MAX_TITLE]) {
    Course*p=head;
    while(p!=nullptr){
        if(strcmp(p->code,c)==0){
            for(int i=0;i<MAX_TITLE;i++){
                p->title[i]=t[i];
            }
            return true;
        }
        p=p->next;
    }
    // TODO: Implementation of modifying a course title

    return false;
}
bool ll_modify_course_credit(Course* head, const char c[MAX_CODE], int cred) {
    
    // TODO: Implementation of modifying a course credit
    Course*p=head;
    while(p!=nullptr){
        if(strcmp(p->code,c)==0){
            p->credit=cred;
            return true;
        }
        p=p->next;
    }
    return false;
}



void ll_cleanup_all(Course *&head) {
   Course*p=head;
   while(p!=nullptr){
    Course*j=head;
    for(j;j!=nullptr;j=j->next){
        ll_delete_exclusion(head,p->code,j->code);
        ll_delete_prerequisite(head,p->code,j->code);
    }
    p=p->next;
   }
   Course*q=head;
   for(q;q!=nullptr;q=q->next){
    ll_delete_course(head,q->code);
   }
    
    // TODO: Implementation of clean up all

}

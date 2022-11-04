#ifndef __PATIENT_H
#define __PATIENT_H
#include <string>
using std::string;
struct Patient {
public:
    int card;
    int illness;
    char doctor[16];
    //Patient(int card, int illness, string doctor);
};
#endif // !__PATIENT_H




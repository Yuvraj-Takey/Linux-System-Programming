#include "header.h"

int main()
{
    int iPriority_Proc = 0;
    int iPriority_Increase = 0;
    int iPid_Proc = 0;

    // get the PID of the process
    iPid_Proc =  getpid();

    // get the current priority of the process
    iPriority_Proc = getpriority(PRIO_PROCESS,iPid_Proc);

    cout<<"[HERE]: The current priority of a process is : "<<iPriority_Proc<<endl;

    // set the new priority to the process
    if(iPriority_Increase = setpriority(PRIO_PROCESS,iPid_Proc,(iPriority_Proc+5)) != STATUS_SUC)
    {
        cout<<"[SORRY]: Unable to set the priority\nReason: "<<strerror(errno)<<endl;
    }
    else
    {
        // get the increased priority of the process
        iPriority_Increase = getpriority(PRIO_PROCESS,iPid_Proc);
        cout<<"[HERE]: The increased priority of a process is : "<<iPriority_Increase<<endl;
    }

    return 0;
}

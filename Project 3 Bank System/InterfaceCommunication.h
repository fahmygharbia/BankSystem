#pragma once
#include <iostream>
using namespace std;

class InterfaceCommunication
{
public:
    virtual void SendEmail(string Tital, string Body) = 0;
    virtual void SendFax(string Tital, string Body) = 0;
    virtual void SendSMS(string Tital, string Body) = 0;
};
#include "Logger.h"
//#include"Utilities.h"
const string CLogger::m_sFileName = "/home/manoj/my_log.log";
CLogger* CLogger:: m_pThis = NULL;
ofstream CLogger::m_Logfile;

CLogger::CLogger()
{
 
}
CLogger* CLogger::getLogger(){
    if(m_pThis == NULL){
        m_pThis = new CLogger();
        m_Logfile.open(m_sFileName.c_str(), ios::out | ios::app );
    }
    return m_pThis;
}
 
void CLogger::Log( const char * format, ... )
{
    char sMessage[512];
    va_list args;
    va_start (args, format);
    vsprintf (sMessage,format, args);
    //m_Logfile <<"\n"<<Util::CurrentDateTime()<<":\t";
    m_Logfile << sMessage << "\n";
    va_end (args);
	m_Logfile.flush();
}
 
void CLogger::Log( const string& sMessage )
{
    //m_Logfile <<"\n"<<Util::CurrentDateTime()<<":\t";
    m_Logfile << sMessage << "\n";
	m_Logfile.flush();
}
 
CLogger& CLogger::operator<<(const string& sMessage )
{
    //m_Logfile <<"\n"<<Util::CurrentDateTime()<<":\t";
    m_Logfile << sMessage << "\n";
	m_Logfile.flush();
    return *this;
}
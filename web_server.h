#ifndef WEBSERVER_H_ /* Include guard */
#define WEBSERVER_H_

 void web_setup(void);
 void web_loop(void);
 String getContentType(String filename);
 bool handleFileRead(String path);
 String getContentType(String filename);

 //note: this supports gz. GZ everything, and minimize it too if you can!

#endif // WEBSERVER_H_
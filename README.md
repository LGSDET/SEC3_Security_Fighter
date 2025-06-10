Here is the install and test guide for the Windows GUI application written by the Security team 3.

1. Install Guide.
 a. Clone below repository.
  - https://github.com/LGSDET/SEC3_Security_Fighter.git

 b. Check if the following files exist in the path "ADS-B-Display\Win64\Release"
  - libcrypto-3-x64.dll
  - libeay32.dll
  - libssl-3-x64.dll
  - ssleay32.dll

 c. Open Project file "ADS-B-Group.groupproj"
 
 d. Build & Execute
 

2. Testing for implemented security features.
 a. Login
   - Execute GUI application
   - Get flight info through SBS or RAW(RaspberryPI) data.
   - Select the plane to show the flight info.
   - Login window will be displayed.
   - Try logging in with the information below.
     - ID : admin
     - PW : Digital_211
   - check the flight info is displayed in Close Control Window.

 b. Encrypted Transfer between GUI app. and Raspberry PI.
   - Generate certificate and key in "dump1090" directory using follow command.
     - openssl req -x509 -newkey rsa:2048 -keyout key.pem -out cert.pem -days 365 -nodes -subj "/CN=your.server.com"
   - Execute "dump1090" using below cmd in RaspberryPI.
     - sudo ./dump1090 --interactive --net
   - Execute "adsbhub.sh" located in "/usr/bin" in RaspberryPI.
     - sudo adsbhub.sh 
   - Check the IP address of the PI within the same network and enter the IP in "Raw Connect" of the GUI application.
   - After the connection is successful, wait until flight information appears in the GUI.
   - When the plane appears, select it and check that the flight information is displayed normally.
   - If you want to check whether the flight information is encrypted, you can check it through the cmd below.
     - openssl s_client -connect <IP address>:30002
       ex) openssl s_client -connect 172.26.51.117:30002

 c. Encrypt record data.
  - Through the SBS or Raw connection, Wait for the flight information to be displayed on the GUI.
  - Select the "Raw record" or "SBS record". Please Specify the directory and file name where data will be saved.
  - Wait until a certain amount of information is recorded.
  - And then, deselect Select the "Raw record" or "SBS record" and disconnect the SBS or Raw connection.
  - If you want to check the data is encrypted correctly, open the saved file using the text tool like "notepad" or "UltraEdit".
  - Save data will show the encrypted time and filght info line by line.
  - To decrypt the saved data, select the "Raw playback" or "SBS playback" and select the saved file.
  - When an plane appears during playback, select it and verify that the "Close Control window" displays the correct information.


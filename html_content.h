#ifndef HTML_CONTENT_H
#define HTML_CONTENT_H

const char HOME_PAGE[] = R"=====(
<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Home</title>
    </head>

    <style>
        body
        {
            color: white;   
            background: linear-gradient(to bottom, #0f0c29, #302b63, #24243e);
        }

        //main center
        .main
        {
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            margin-top: 50px;
        }

        .form {
            display: flex;
            flex-direction: column;
        }

        .form-group {
            margin-bottom: 10px;
        }

        label {
            width: 100px; /* Atur lebar label */
            display: inline-block;
            vertical-align: top; /* Atur posisi label agar sejajar dengan input */
        }

        input[type='text'] {
            width: 200px; /* Atur lebar input */
            padding: 5px;
        }

        .flex-container {
            display: flex;
            align-items: center; /* Menyamakan ketinggian elemen */
        }

        h4 {
            margin-right: 10px; /* Memberikan jarak kanan antara h4 dan button */
        }


        button[type='submit'] {
            padding: 10px;
            background-color: #4CAF50;
            color: #000000;
            border: none;
            cursor: pointer;
            width: 150px;
        }

        table {
            border-collapse: collapse;
            width: 300px;
            font-size: 14px;
        }

        table th,
        table td {
            border: 1px solid #ddd; /* Membuat border untuk sel header dan sel data */
            padding: 8px; /* Menambahkan padding agar konten tidak terlalu rapat dengan border */
        }

        table th {
            background-color: #f2f2f2;
            color: #333;
            font-weight: bold;
        }

        table tr:nth-child(even) {
            background-color: #000000;
        }

        checkbox {
            margin-left: 5px;
            width: 10px;
        }

        //responsive with mobile
        @media screen and (max-width: 600px) {
            label {
                width: auto; /* Mengatur lebar label sesuai dengan teks di dalamnya */
            }
            
            input[type='text'] {
                width: 100%; /* Mengatur lebar input agar mengisi keseluruhan lebar kontainer */
            }
            
            button, button[type='submit'] {
                width: 100%; /* Mengatur lebar tombol agar mengisi keseluruhan lebar kontainer */
            }

            table {
                font-size: 10px;
                width: 35%; /* Mengatur lebar tabel agar mengisi keseluruhan lebar kontainer */
            }
        }
    </style>

    <body>
        <div class="main">
            <div>
                <h1>Access Point Management</h1>
                <form action='/updateWifi' method='post' class='form'>
                    <div class='form-group'>
                        <label>SSID</label>
                        <input type='text' name='ssid' value={{ssid}} required>
                    </div>
                    <div class='form-group'>
                        <label>Password</label>
                        <input type='text' name='password'' value={{password}} required>
                    </div>
                    <button type='submit'>Update</button>
                </form>
            </div>
            <hr>
            <div>
                <h1>Network Management</h1>
                    <div>
                        <form action='/updateNetworkAccessPoint' method='post' class='form'>
                            <h2>Access Point</h2>
                            <div class='form-group'>
                                <label for='ipAP'>IP Address Access Point</label>
                                <input type='text' id='ipAP' name='ipAP' value='{{ipAP}}' required>
                            </div>
                            <button type='submit'>Update Access Point</button>
                        </form>
                    </div>
                    <div>
                        <form action='/updateNetworkStation' method='post' class='form'>
                            <h2>Station</h2>
                            <div class='form-group'>
                                <label for='ipLocal'>IP Address Local</label>
                                <input type='text' id='ipLocal' name='ipLocal' value='{{ipLocal}}' required>
                            </div>
                            <div class='form-group'>
                                <label for='gateway'>Gateway</label>
                                <input type='text' id='gateway' name='gateway' value='{{gatewayIP}}' required>
                            </div>
                            <div class='form-group'>
                                <label for='subnetmask'>Subnet Mask</label>
                                <input type='text' id='subnetmask' name='subnetmask' value='{{subnetmaskIP}}' required>
                            </div>
                            <div class='form-group'>
                                <label for='dns1'>DNS 1</label>
                                <input type='text' id='dns1' name='dns1' value='{{dns1}}' required>
                            </div>
                            <div class='form-group'>
                                <label for='dns2'>DNS 2</label>
                                <input type='text' id='dns2' name='dns2' value='{{dns2}}' required>
                            </div>
                            <button type='submit'>Update Station</button>
                        </form>
                    </div>
                </form>
            </div>
            <hr>
            <div>
                <h1>Device Management</h1>
                <div>
                    <h2>Device List</h2>
                    <div>
                        <div class="flex-container">
                            <button onclick="window.location.reload()" style="padding: 10px; background-color: #FFFF00; color: #000000; border: none; cursor: pointer; width: 150px;">Refresh</button>
                            <div style="margin-left: 10px;">
                                <h4>Total Device: {{totalDevices}}</h4>
                            </div>
                        </div>
                        {{deviceList}}
                    </di>
                </div>
            </div>
            <hr>
            <div>
            <h1>Wi-Fi Management</h1>
                <div>
                    <div>
                        <h2>Connected with Wi-Fi: {{ssidTarget}}</h2>
                        <p>Disconnect from Wi-Fi?</p>
                        <form action='/disconnect' method='post' class='form'>
                            <div class="flex-container">
                                <button type='submit'>Disconnect</button>
                                <div style="margin-left: 10px;">
                                    <input type='checkbox' name='checkboxResetSSID' value='yes'>
                                    <label for='checkboxResetSSID'>Reset SSID & Password?</label>
                                </div>
                            </div>
                        </form>
                    </div>
                </div>
                <div>
                    <div>
                        <h2>Wi-Fi List</h2>
                    </div>
                    <div>
                        <div class="flex-container">
                        <button onclick="window.location.reload()" style="padding: 10px; background-color: #FFFF00; color: #000000; border: none; cursor: pointer; width: 150px;">Refresh</button>
                            <div style="margin-left: 10px;">
                                <h4>Total Wifi: {{totalWifi}}</h4>
                            </div>
                        </div>
                        {{wifiList}}
                    </div>
                </div>
                <div>
                    <form action='/connect' method='post' class='form'>
                        <div>
                            <h2>Connect to WiFi</h2>
                            <div class='form-group'>
                                <label>SSID</label>
                                <input type='text' name='ssidTarget' required>
                            </div>
                            <div class='form-group'>
                                <label>Password</label>
                                <input type='text' name='passwordTarget'>
                            </div>
                        </div>
                        <div>
                            <h2>Rename WiFi after connect</h2>
                            <div class='form-group'>
                                <label>SSID</label>
                                <input type='text' name='ssidToConnected' value={{ssidRenamed}} required>
                            </div>
                            <div class='form-group'>
                                <label>Password</label>
                                <input type='text' name='passwordToConnected' value={{passwordRenamed}} required>
                            </div>
                        </div>
                        <button type='submit'>Connect</button>
                    </form>
                </div>
            </div>
            <hr>
            <div>
                <h1>Profile</h1>
                <form action='/updateProfile' method='post' class='form'>
                <div class='form-group'>
                    <label>Nama</label>
                    <input type='text' name='username' value="{{adminUsername}}" required>
                </div>
                <div class='form-group'>
                    <label>Password</label>
                    <input type='text' name='password'' value="{{adminPassword}}" required>
                </div>
                <button type='submit'>Update</button>
                </form>
            </div>
            <hr>
            <div>
                <h1>Menu</h1>
                <div>
                    <h2>Logout</h2>
                    <form action='/logout' method='post' class='form'>
                        <button type='submit' style="padding: 10px; background-color: #FFFF00; color: #000000; border: none; cursor: pointer; width: 150px;">Logout</button>
                    </form>
                </div>
                <div>
                    <h2>Reset to Default</h>
                    <form action='/resetToDefault' method='post' class='form'>
                        <button type='submit' style="padding: 10px; background-color: #FFFF00; color: #000000; border: none; cursor: pointer; width: 150px;">reset</button>
                    </form>
                </div>
            </div>
    </body>
</html>
)=====";

const char LOGIN_PAGE[] = R"=====(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
	<title>Login</title>
    <style>
        body{
            margin: 0;
            padding: 0;
            display: flex;
            justify-content: center;
            align-items: center;
            min-height: 100vh;
            font-family: 'Jost', sans-serif;
            background: linear-gradient(to bottom, #0f0c29, #302b63, #24243e);
        }
        .main{
            width: 400px;
            height: 500px;
            background: red;
            overflow: hidden;
            background: linear-gradient(to bottom, #0f0c29, #302b63, #24243e);
            border-radius: 10px;
            box-shadow: 5px 20px 50px #000;
        }

        .login{
            position: relative;
            width:100%;
            height: 100%;
        }
        label{
            color: #fff;
            font-size: 2.3em;
            justify-content: center;
            display: flex;
            margin: 60px;
            font-weight: bold;
        }
        input{
            width: 60%;
            height: 20px;
            background: #e0dede;
            justify-content: center;
            display: flex;
            margin: 20px auto;
            padding: 10px;
            border: none;
            outline: none;
            border-radius: 5px;
        }
        button{
            width: 60%;
            height: 40px;
            margin: 10px auto;
            justify-content: center;
            display: block;
            color: #fff;
            background: #573b8a;
            font-size: 1em;
            font-weight: bold;
            margin-top: 20px;
            outline: none;
            border: none;
            border-radius: 5px;
            transition: .2s ease-in;
            cursor: pointer;
        }
        button:hover{
            background: #6d44b8;
        }
    </style>
</head>
<body>
	<div class="main">  	
        <div class="login">
            <form action = "/login" method = "post">
                <label >Login</label>
                <input type="text" name="username" placeholder="Username" required>
                <input type="password" name="password" placeholder="Password" required>
                <button type="submit"> Login</ button>
            </form>
        </div>
	</div>
</body>
</html>
)=====";


const char MESSAGES_PAGE[] = R"=====(
<!DOCTYPE html>
<html>
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Messages</title>
    </head>
    <body>
        <div>
            <h1>{{messages}}</h1>
            <button onclick="window.location.href='/'">Back</button>
        </div>
    </body>
</html>

)=====";

#endif

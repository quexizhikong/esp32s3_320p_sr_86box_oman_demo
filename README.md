
## 更新说明(Update Records)：

### v1.0.0
* 1. esp-box:0.3.0
* 2. esp-sr:dev2.0

## HMI Eenvironment：
* 1. GUI-Guider-1.6.1-GA

## 编译环境(Compilation Eenvironment)：
* 1. https://github.com/espressif/esp-idf/releases/tag/v4.4.6
* 2. 或者https://dl.espressif.com/github_assets/espressif/esp-idf/releases/download/v4.4.6/esp-idf-v4.4.6.zip

## 语音助手(ESP-Skainet)：
* 1. https://github.com/espressif/esp-box.git
* 2. https://github.com/espressif/esp-skainet.git
* 3. https://github.com/espressif/esp-sr.git

## 编译建议(Compilation suggestions)：
* rm -rf .git
* git init 
* git config core.autocrlf false
* git add .
* git commit -m "first commit"
* git push -u origin "master"
* git push origin release/v1.0
* idf.py -p com7 -b 921600 flash
* idf.py -p com7 -b 921600 app-flash
* idf.py -p com7 -b 921600 app-flash monitor








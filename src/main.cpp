#ifndef __JNI__
#ifndef __CLIB__
#include <cstdio>
#include "main.h"
#include "version.h"
#include "OcrLite.h"
#include "OcrUtils.h"
#include <stdio.h>
#include <conio.h>
#include "ScreenShot.h"
#include <iostream>
#include <Windows.h>



using namespace cv;


HHOOK hHook{ NULL };
int totalcount = 1;
int OCR();

LRESULT CALLBACK keyboard_hook(const int code, const WPARAM wParam, const LPARAM lParam) {
	if (wParam == WM_KEYDOWN) {              
        PKBDLLHOOKSTRUCT p = ( PKBDLLHOOKSTRUCT ) lParam;
              if ( p->vkCode == VK_RETURN)
              {
                Screenshot screenshot;
                Mat img = screenshot.getScreenshot();
                imwrite("screenshot" + std::to_string(totalcount) + ".jpg", img);
                totalcount++;
              } else if ( p->vkCode == VK_ESCAPE) {
                  OCR();
                  UnhookWindowsHookEx(hHook);
              }
	}

	return CallNextHookEx(hHook, code, wParam, lParam);
}


int main(int argc, char **argv) {
    system("chcp 65001");
    printf("按enter截图，按esc结束截图");

    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboard_hook, NULL, 0);
	if (hHook == NULL) {
		std::cout << "Keyboard hook failed!" << std::endl;
	}
    while (GetMessage(NULL, NULL, 0, 0));

    return 0;
}

int OCR() 
{
    std::cout << "OCR STARTED" << std::endl;
    std::string modelsDir, modelDetPath, modelClsPath, modelRecPath, keysPath;
    std::string imgPath, imgDir, imgName;
    int numThread = 4;
    int padding = 50;
    int maxSideLen = 1024;
    float boxScoreThresh = 0.6f;
    float boxThresh = 0.3f;
    float unClipRatio = 2.0f;
    bool doAngle = true;
    int flagDoAngle = 1;
    bool mostAngle = true;
    int flagMostAngle = 1;
    modelsDir = "./models";

    int opt;
    int optionIndex = 0;




    if (modelDetPath.empty()) {
        modelDetPath = modelsDir + "/" + "dbnet.onnx";
    }
    if (modelClsPath.empty()) {
        modelClsPath = modelsDir + "/" + "angle_net.onnx";
    }
    if (modelRecPath.empty()) {
        modelRecPath = modelsDir + "/" + "crnn_lite_lstm.onnx";
    }
    if (keysPath.empty()) {
        keysPath = modelsDir + "/" + "keys.txt";
    }
    bool hasTargetImgFile = isFileExists(imgPath);
    if (!hasTargetImgFile) {
        fprintf(stderr, "Target image not found: %s\n", imgPath.c_str());
        return -1;
    }
    bool hasModelDetFile = isFileExists(modelDetPath);
    if (!hasModelDetFile) {
        fprintf(stderr, "Model dbnet file not found: %s\n", modelDetPath.c_str());
        return -1;
    }
    bool hasModelClsFile = isFileExists(modelClsPath);
    if (!hasModelClsFile) {
        fprintf(stderr, "Model angle file not found: %s\n", modelClsPath.c_str());
        return -1;
    }
    bool hasModelRecFile = isFileExists(modelRecPath);
    if (!hasModelRecFile) {
        fprintf(stderr, "Model crnn file not found: %s\n", modelRecPath.c_str());
        return -1;
    }
    bool hasKeysFile = isFileExists(keysPath);
    if (!hasKeysFile) {
        fprintf(stderr, "keys file not found: %s\n", keysPath.c_str());
        return -1;
    }
    OcrLite ocrLite;
    ocrLite.setNumThread(numThread);
    ocrLite.initLogger(
            true,//isOutputConsole
            false,//isOutputPartImg
            true);//isOutputResultImg

    ocrLite.enableResultTxt(imgDir.c_str(), imgName.c_str());
    ocrLite.Logger("=====Input Params=====\n");
    ocrLite.Logger(
            "numThread(%d),padding(%d),maxSideLen(%d),boxScoreThresh(%f),boxThresh(%f),unClipRatio(%f),doAngle(%d),mostAngle(%d)\n",
            numThread, padding, maxSideLen, boxScoreThresh, boxThresh, unClipRatio, doAngle, mostAngle);

    ocrLite.initModels(modelDetPath, modelClsPath, modelRecPath, keysPath);

    OcrResult result = ocrLite.detect(imgDir.c_str(), imgName.c_str(), padding, maxSideLen,
                                      boxScoreThresh, boxThresh, unClipRatio, doAngle, mostAngle);
    ocrLite.Logger("%s\n", result.strRes.c_str());
    return 1;
}




#endif
#endif
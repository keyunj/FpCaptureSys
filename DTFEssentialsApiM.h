#pragma once
//
// DTFEssentialsApiM.h
//
// This module include  scanner SDK.
//


#ifndef __ESSENTIALS_API_M_H__
#define __ESSENTIALS_API_M_H__

#include "DTFEssentialsApi.h"

#ifdef __cplusplus
extern "C" {
#endif

    ////////////////////////////////////////////////////////////////////////////////
    // Error codes

    // Macros
#define MAX_DEVICE_NUM             10                 ///< maximum device number


// Connected scanner
    typedef struct tagDTFMScannerExist
    {
        int nDevConnected;  ///< Number of connected devices
        int n500;
        DTFScannerType scannerType[MAX_DEVICE_NUM];     ///< scanner type, A mapping of array element onto device index. 
    } DTFMScannerExist;

    ////////////////////////////////////////////////////////////////////////////////
    // Interface

    //------------------------------------------------------------------- 
    // Function name: M_Main_GetConnectedScanner
    // Parameter:
    //    input:  
    //    output: 
    //    in/out: scannerExist - connected scanner; memory provided by caller!
    // Return:
    //    STATUS_OK
    //    ERR_INVALID_PARAM_VALUE
    // Description: Get connected scanner devices.
    //------------------------------------------------------------------- 
    int WINAPI M_Main_GetConnectedScanner(DTFMScannerExist* scannerExist);

    //------------------------------------------------------------------- 
    // Function name: M_Main_GetAPIVersion
    // Parameter:
    //    input:  
    //    output: 
    //    in/out: info - API version information; memory provided by caller!
    // Return:
    //    STATUS_OK
    //    ERR_INVALID_PARAM_VALUE
    // Description: Get DLL version information.
    //------------------------------------------------------------------- 
    int WINAPI M_Main_GetAPIVersion(DTFApiVersion* info);

    //------------------------------------------------------------------- 
    // Function name: M_Main_GetRunningInfo
    // Parameter:
    //    input:  handle - Device handle obtained by M_Main_Initialize()
    //    output: 
    //    in/out: info - Device running information; memory provided by caller!
    // Return:
    //    STATUS_OK
    //    ERR_INVALID_PARAM_VALUE
    // Description: Get Running information.
    //------------------------------------------------------------------- 
    int WINAPI M_Main_GetRunningInfo(const int handle, DTFRunningInfo* info);

    //------------------------------------------------------------------- 
    // Function name: M_Main_Initialize
    // Parameter:
    //    input:  deviceIndex - Zero-based device index for device to init
    //    output: 
    //    in/out: handle - Function returns device handle to be used for subsequent function calls
    // Return:
    //    STATUS_OK
    //    ERR_IS_INITIALIZED
    //    ERR_DEVICE_IO
    // Description: Initialize scanner.
    //------------------------------------------------------------------- 
    int WINAPI M_Main_Initialize(const int deviceIndex, int* handle);

    //------------------------------------------------------------------- 
    // Function name: M_Main_DeInitialize
    // Parameter:
    //    input:  handle - Device handle obtained by M_Main_Initialize()
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    // Description: DeInitialize scanner.
    //------------------------------------------------------------------- 
    int WINAPI M_Main_DeInitialize(const int handle);

    //------------------------------------------------------------------- 
    // Function name: M_Main_DeInitializeAll
    // Parameter:
    //    input:  
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    // Description: DeInitialize all currently initialized scanner.
    //------------------------------------------------------------------- 
    int WINAPI M_Main_DeInitializeAll();

    //------------------------------------------------------------------- 
    // Function name: M_Main_IsInitialized
    // Parameter:
    //    input:  
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK -> device is ready to be used.
    // Description: Check if device is fully initialized.
    //------------------------------------------------------------------- 
    int WINAPI M_Main_IsInitialized(const int handle);

    //------------------------------------------------------------------- 
    // Function name: M_Main_GetDeviceInfo
    // Parameter:
    //    input:  handle - Device handle obtained by M_Main_Initialize()
    //    output: 
    //    in/out: info - Basic device information; memory provided by caller!
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Retrieve detailed device information.
    //------------------------------------------------------------------- 
    int WINAPI M_Main_GetDeviceInfo(const int handle, DTFPropertyInfo* info);

    //------------------------------------------------------------------- 
    // Function name: M_Capture_SetMode
    // Parameter:
    //    input:  handle - Device handle obtained by M_Main_Initialize()
    //            imageType - Image type to capture
    //            imageResolution - Requested capture resolution
    //            AutoCapture - Flag to auto capture
    //            AutoContrast - Flag to auto contrast
    //    output: 
    //    in/out: *resultWidth - Returns width of captured result image in pixels
    //            *resultHeight - Returns height of captured result image in pixels
    //            *baseResolutionX - Returns image horizontal base resolution before processing
    //            *baseResolutionY - Returns image vertical base resolution before processing
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    //    ERR_COMMAND_FAILED
    //    ERR_NOT_SUPPORTED
    // Description: Set capture mode.
    //              This function needs to be called prior to M_Capture_Start().
    //------------------------------------------------------------------- 
    int WINAPI M_Capture_SetMode(
        const int                  handle,
        const DTFImageType         imageType,
        const DTFImageResolution   imageResolution,
        BOOL                       AutoCapture,
        BOOL                       AutoContrast,
        int* resultWidth,
        int* resultHeight,
        int* baseResolutionX,
        int* baseResolutionY
    );

    //------------------------------------------------------------------- 
    // Function name: M_Capture_Start
    // Parameter:
    //    input:  handle - Device handle obtained by M_Main_Initialize() 
    //            numberOfObjects - Number of expected fingertips in the image
    //            AutoAcquireResultImage - Auto acquire result image flag
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    //    ERR_IS_CAPTUREING
    // Description: Start image acquisition.
    //------------------------------------------------------------------- 
    int WINAPI M_Capture_Start(const int handle, const int numberOfObjects, BOOL AutoAcquireResultImage = TRUE);

    //------------------------------------------------------------------- 
    // Function name: Capture_Abort
    // Parameter:
    //    input:  handle - Device handle obtained by M_Main_Initialize() 
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    // Description: Abort running image acquisition.
    //------------------------------------------------------------------- 
    int WINAPI M_Capture_Abort(const int handle);

    //------------------------------------------------------------------- 
    // Function name: M_Capture_TakeResultImage
    // Parameter:
    //    input:  handle - Device handle obtained by M_Main_Initialize() 
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    // Description: Initiate manual result image acquisition.
    //              This function needs to be called prior to M_Capture_AcquireResultImage().
    //------------------------------------------------------------------- 
    int WINAPI M_Capture_TakeResultImage(const int handle);

    //------------------------------------------------------------------- 
    // Function name: M_Capture_AcquireResultImage
    // Parameter:
    //    input:  handle - Device handle obtained by M_Main_Initialize() 
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    // Description: Acquire the result image, it might take several seconds, expect a delay
    //------------------------------------------------------------------- 
    int WINAPI M_Capture_AcquireResultImage(const int handle);

    //------------------------------------------------------------------- 
    // Function name: M_Controls_SetStateLEDs
    // Parameter:
    //    input:  handle - Device handle obtained by M_Main_Initialize() 
    //            CapTypeApi - Image type to active status LED's
    //            StateLEDs - show type of active LED's  
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Set active status LED's on the device.
    //------------------------------------------------------------------- 
    int WINAPI M_Controls_SetStateLEDs(const int handle, DTFImageType CapTypeApi, unsigned char* StateLEDs);

    //------------------------------------------------------------------- 
    // Function name: M_Controls_SetStateLEDs
    // Parameter:
    //    input:  handle - Device handle obtained by M_Main_Initialize() 
    //            CapTypeApi - Image type to active status LED's
    //            iColor - show color of active LED's  
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Set active status LED's on the device.
    //------------------------------------------------------------------- 
    int WINAPI M_Controls_SetFingerLEDs(const int handle, DTFImageType CapTypeApi, LEDColor iColor);

    //------------------------------------------------------------------- 
    // Function name: M_Controls_SetLEDs
    // Parameter:
    //    input:  handle - Device handle obtained by M_Main_Initialize() 
    //            ledType - show type of active LED's
    //            ledValue - value of the status LED
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Set active LED's on the device.
    //------------------------------------------------------------------- 
    int WINAPI M_Controls_SetLEDs(const int handle, DTFLedType ledType, int ledValue);

    //------------------------------------------------------------------- 
    // Function name: M_Controls_GetLEDs
    // Parameter:
    //    input:  handle - Device handle obtained by M_Main_Initialize() 
    //            ledType - show type of active LED's
    //            ledValue - Led's value
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Set active LED's on device.
    //------------------------------------------------------------------- 
    int WINAPI M_Controls_GetLEDs(const int handle, DTFLedType ledType, int* ledValue);

    //-------------------------------------------------------------------     
    // Function name: M_Controls_Beeper
    // Parameter:
    //    input:  handle - Device handle obtained by M_Main_Initialize() 
    //            BeepMode - Beeper mode
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_NOT_SUPPORTED
    // Description: Send beep pattern to internal device beeper.
    //------------------------------------------------------------------- 
    int WINAPI M_Controls_Beeper(const int handle, int BeepMode);

    //------------------------------------------------------------------- 
    // Function name: M_Capture_SetCaptureOK
    // Parameter:
    //    input:  handle - Device handle obtained by M_Main_Initialize() 
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    // Description: Set captured flag is OK.
    //------------------------------------------------------------------- 
    int WINAPI M_Capture_SetCaptureOK(const int handle);

    //------------------------------------------------------------------- 
    // Function name: M_Capture_SetStartRollingFlag
    // Parameter:
    //    input:  handle - Device handle obtained by M_Main_Initialize() 
    //            flag - Flag to start rolling
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    // Description: Set start rolling flag.
    //------------------------------------------------------------------- 
    int WINAPI M_Capture_SetStartRollingFlag(const int handle, BOOL flag);

    //------------------------------------------------------------------- 
    // Function name: M_Capture_GetRollParameters
    // Parameter:
    //    input:  handle - Device handle obtained by M_Main_Initialize() 
    //    output: 
    //    in/out: para - Roll construct parameters; memory provided by caller!
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Get roll parameters.
    //------------------------------------------------------------------- 
    int WINAPI M_Capture_GetRollParameters(const int handle, DFRollParameters* para);

    //------------------------------------------------------------------- 
    // Function name: M_Capture_SetRollParameters
    // Parameter:
    //    input:  handle - Device handle obtained by M_Main_Initialize() 
    //            para - Roll construct parameters;
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Set roll parameters.
    //------------------------------------------------------------------- 
    int WINAPI M_Capture_SetRollParameters(const int handle, DFRollParameters para);

    //------------------------------------------------------------------- 
    // Function name: Capture_Calibration
    // Parameter:
    //    input:  handle - Device handle obtained by M_Main_Initialize() 
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_MEM_ALLOC
    //    ERR_COMMAND_FAILED
    // Description: Calibrate scanner.
    //------------------------------------------------------------------- 
    int WINAPI M_Capture_Calibration(const int handle);

    //------------------------------------------------------------------- 
    // Function name: M_Controls_RegisterFootSwitchInfo
    // Parameter:
    //    input:  handle - Device handle obtained by M_Main_Initialize() 
    //            hWnd - windows handler to display live image
    //            Msg - footswitch message id
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    // Description: Register Footswitch information.
    //------------------------------------------------------------------- 
    int WINAPI M_Controls_RegisterFootSwitchInfo(const int handle, HWND hWnd, UINT Msg);

    //------------------------------------------------------------------- 
    // Function name: M_Capture_RegisterCallbackPreviewImage
    // Parameter:
    //    input:  handle - Device handle obtained by M_Main_Initialize() 
    //            callback - Pointer to the notification function 
    //            context - Pointer to user context; this value is used 
    //                      as parameter for callback
    //    output: 
    //    in/out:
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Callback preview image availability.
    //------------------------------------------------------------------- 
    int WINAPI M_Capture_RegisterCallbackPreviewImage(
        const int                  handle,
        CallbackPreviewImage   callback,
        void* context
    );

    //------------------------------------------------------------------- 
    // Function name: M_Capture_RegisterCallbackTakingResultImage
    // Parameter:
    //    input:  handle - Device handle obtained by M_Main_Initialize() 
    //            callback - Pointer to the notification function 
    //            context - Pointer to user context; this value is used 
    //                      as parameter for callback
    //    output: 
    //    in/out:
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Callback for start of result image capture.
    //------------------------------------------------------------------- 
    int WINAPI M_Capture_RegisterCallbackTakingResultImage(
        const int                       handle,
        CallbackTakingResultImage   callback,
        void* context
    );

    //------------------------------------------------------------------- 
    // Function name: M_Capture_RegisterCallbackResultImage
    // Parameter:
    //    input:  handle - Device handle obtained by M_Main_Initialize() 
    //            callback - Pointer to the notification function 
    //            context - Pointer to user context; this value is used 
    //                      as parameter for callback
    //    output: 
    //    in/out:
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Callback for completion of result image acquisition.
    //------------------------------------------------------------------- 
    int WINAPI M_Capture_RegisterCallbackResultImage(
        const int               handle,
        CallbackResultImage callback,
        void* context
    );

    //------------------------------------------------------------------- 
    // Function name: M_Capture_RegisterCallbackFootSwitch
    // Parameter:
    //    input:  handle - Device handle obtained by M_Main_Initialize() 
    //            callback - Pointer to the notification function 
    //            context - Pointer to user context; this value is used 
    //                      as parameter for callback
    //    output: 
    //    in/out:
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Callback for message of trigger Footswitch.
    //------------------------------------------------------------------- 
    int WINAPI M_Capture_RegisterCallbackFootSwitch(
        const int               handle,
        CallbackFootSwitch  callback,
        void* context
    );

    //------------------------------------------------------------------- 
    // Function name: M_Capture_RegisterCallbackKeypad
    // Parameter:
    //    input:  handle - Device handle obtained by M_Main_Initialize() 
    //            callback - Pointer to the notification function 
    //            context - Pointer to user context; this value is used 
    //                      as parameter for callback
    //    output: 
    //    in/out:
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Callback for message of trigger Keypad.
    //------------------------------------------------------------------- 
    int WINAPI M_Capture_RegisterCallbackKeypad(
        const int               handle,
        CallbackKeypad      callback,
        void* context
    );

    //------------------------------------------------------------------- 
    // Function name: M_Capture_RegisterCallbackObjectQuality
    // Parameter:
    //    input:  handle - Device handle obtained by M_Main_Initialize() 
    //            callback - Pointer to the notification function 
    //            context - Pointer to user context; this value is used 
    //                      as parameter for callback
    //    output: 
    //    in/out:
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Register callback function for fingertip qualities change during capture operation.
    //------------------------------------------------------------------- 
    int WINAPI M_Capture_RegisterCallbackObjectQuality(
        const int                   handle,
        CallbackObjectQuality   callback,
        void* context
    );

    //------------------------------------------------------------------- 
    // Function name: M_Capture_RegisterCallbackDeviceIsConnected
    // Parameter:
    //    input:  handle - Device handle obtained by M_Main_Initialize() 
    //            callback - Pointer to the notification function 
    //            context - Pointer to user context; this value is used 
    //                      as parameter for callback
    //    output: 
    //    in/out:
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Register callback function for the current equipment is exist.
    //------------------------------------------------------------------- 
    int WINAPI M_Capture_RegisterCallbackDeviceIsConnected(
        const int                       handle,
        CallbackDeviceIsConnected   callback,
        void* context
    );

    //------------------------------------------------------------------- 
    // Function name: M_Capture_GetImageMask
    // Parameter:
    //    input:  handle - Device handle obtained by M_Main_Initialize() 
    //    output: 
    //    in/out: pImageMask - Rolling mask image; memory provided by caller!
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Get rolling mask image.
    //------------------------------------------------------------------- 
    int WINAPI M_Capture_GetImageMask(
        const int       handle,
        unsigned char* pImageMask
    );

    //------------------------------------------------------------------- 
    // Function name: M_Capture_SetAutoCapInfo
    // Parameter:
    //    input:  handle - Device handle obtained by M_Main_Initialize() 
    //            para - Auto capture information
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    // Description: Set auto capture information.
    //------------------------------------------------------------------- 
    int WINAPI M_Capture_SetAutoCapInfo(
        const int       handle,
        DTFAutoCapInfo  para
    );

    //------------------------------------------------------------------- 
    // Function name: M_Capture_SetAutoCapArea
    // Parameter:
    //    input:  handle - Device handle obtained by M_Main_Initialize() 
    //            bAutoCapArea - auto capture area flag
    //            xPos - x coordinate
    //            yPos - y coordinate
    //            width - the width of the area
    //            height - the height of the area
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    // Description: Set auto capture area information image.
    //------------------------------------------------------------------- 
    int WINAPI M_Capture_SetAutoCapArea(
        const int       handle,
        BOOL bAutoCapArea, int xPos = 0, int yPos = 0, int width = 0, int height = 0);

    //------------------------------------------------------------------- 
    // Function name: M_Capture_SetAutoCapFinMask
    // Parameter:
    //    input:  handle - Device handle obtained by M_Main_Initialize() 
    //            nFinMask - finger mask.
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    // Description: Set auto capture finger mask.
    //------------------------------------------------------------------- 
    int WINAPI M_Capture_SetAutoCapFinMask(
        const int       handle,
        int nFinMask);

    //------------------------------------------------------------------- 
    // Function name: M_Control_CmdSetValue
    // Parameter:
    //    input: handle - Device handle obtained by M_Main_Initialize() 
    //           dwCommandMask - command mask.
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Set command mask.
    //------------------------------------------------------------------- 
    int WINAPI M_Control_CmdSetValue(
        const int       handle,
        DWORD dwCommandMask = CMD_MASK);

    //------------------------------------------------------------------- 
    // Function name: M_Capture_RegisterCallbackSensorIsDirty
    // Parameter:
    //    input:  Callback function entry pointer
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Register callback function which is invoked when dirty sensor surface is detected.
    //------------------------------------------------------------------- 
    int WINAPI M_Capture_RegisterCallbackSensorIsDirty(
        const int					handle,
        CallbackSensorIsDirty   callback,
        void* context
    );

    //------------------ Only for DEMO_TEST project ------------------
//     int WINAPI M_LateralCutAdjust();
//     int WINAPI M_Set_VideoProp(int VideoID, int Value);


    //add hw
    //------------------------------------------------------------------- 
    // Function name: Control_RemoveFog
    // Parameter:
    //    input: handle - Device handle obtained by M_Main_Initialize() 
    //    bFlag - Flag of Remove fog (turn on/off)
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Setting a flag of remove fog from image
    //------------------------------------------------------------------- 
    int WINAPI M_Control_RemoveFog(
        const int       handle,
        BOOL            bFlag);

    //------------------------------------------------------------------- 
    // Function name: M_Capture_FPSegment
    // Parameter:
    //    input: handle - Device handle obtained by M_Main_Initialize() 
    //    input: imageType - flat type
    //	  input: pRawImg - flat image
    //    input: iWidth - image width
    //    input: iHeight - image height
    //    input/output: pSegFPData - segment single finger image data of the flat image
    //    input/output: NumSegFinger - Number of finger
    //    input/output: pszErrMsg - error message
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Segment flat image
    //------------------------------------------------------------------- 
    int WINAPI M_Capture_FPSegment(
        const int                   handle,
        const DTFImageType          imageType,
        BYTE* pRawImg,
        int							iWidth,
        int							iHeight,
        SegFPData* pSegFPData,
        int* NumSegFinger,
        char* pszErrMsg
    );

    int WINAPI M_Capture_Raw2Wsq(
        const int                   handle,
        int nHeight,
        int nWidth,
        int nBitsCount,
        UCHAR* pucRawBuf,
        int* pnWSQBufLen,
        UCHAR** ppucWSQBuf,
        float fRatio
    );
    int WINAPI M_Capture_GetTemplate(
        const int                   handle,
        unsigned char* Image,
        int ImgWidth,
        int ImgHeight,
        int FingerPosition,
        int TemplateType,
        unsigned char** Template,
        int* TemplateSize);


    //------------------------------------------------------------------- 
    // Function name: M_Capture_IsTrueFinger
    // Parameter:
    //    input: handle - Device handle obtained by M_Main_Initialize() 
    //    input: Image - flat image
    //    input: iWidth - image width
    //    input: iHeight - image height
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Setting a flag of remove fog from image
    //------------------------------------------------------------------- 
    int WINAPI M_Capture_IsTrueFinger(
        const int       handle,
        unsigned char* Image,
        int             iWidth,
        int             iHeight
    );
#ifdef __cplusplus
} // extern "C"
#endif

#endif    // __ESSENTIALS_API_M_H__

////////////////////////////////////////////////////////////////////////////////

#pragma once
//
// DTFEssentialsApi.h
//



#ifndef __ESSENTIALS_API_H__
#define __ESSENTIALS_API_H__

#include "windows.h"

#ifdef __cplusplus
extern "C" {
#endif

    ////////////////////////////////////////////////////////////////////////////////
    // Error codes
#define STATUS_OK                           (0)                    ///< Function completed successfully

    // Generic Error Codes
#define GENERIC_ERR                         (0) 
#define ERR_INVALID_PARAM_VALUE             (GENERIC_ERR-1)    ///< Invalid parameter value
#define ERR_MEM_ALLOC                       (GENERIC_ERR-2)    ///< Insufficient memory
#define ERR_NOT_SUPPORTED                   (GENERIC_ERR-3)    ///< Requested functionality isn't supported
#define ERR_FILE_OPEN                       (GENERIC_ERR-4)    ///< File open failed
#define ERR_FILE_READ                       (GENERIC_ERR-5)    ///< File read failed
#define ERR_THREAD_RESUME_ERR               (GENERIC_ERR-6)    ///< Resume thread failed
#define ERR_THREAD_CREATE_ERR               (GENERIC_ERR-7)    ///< Create thread failed
#define ERR_EVENT_CREATE_ERR                (GENERIC_ERR-8)    ///< Create event failed
#define ERR_LOG_LEVEL_LOW                   (GENERIC_ERR-9)    ///< Log level is lowly
#define ERR_LOG_DIRECTORY_IS_NO_EXIST       (GENERIC_ERR-10)   ///< Log directory is no exist
#define ERR_DIRECTORY_CREATE                (GENERIC_ERR-11)   ///< Directory create failed

#define ERR_FILE_WRITE                      (GENERIC_ERR-12)    ///< File write failed

    // Device Related Error Codes
#define DEVICE_ERR                          (-600)
#define ERR_DEVICE_IO                       (DEVICE_ERR-0)     ///< Device communication failed
#define ERR_COMMAND_FAILED                  (DEVICE_ERR-1)     ///< Command execution failed
#define ERR_COMMAND_TIMEOUT                 (DEVICE_ERR-2)     ///< Command execution timed out
#define ERR_NO_DEVICE                       (DEVICE_ERR-3)     ///< No device is detected/active
#define ERR_NO_MATCHING_DEVICE              (DEVICE_ERR-4)     ///< No matching device is detected
#define ERR_DEVICE_ACTIVE                   (DEVICE_ERR-5)     ///< Initialization failed because in use by another thread/process
#define ERR_NOT_INITIALIZED                 (DEVICE_ERR-6)     ///< Device needs to be initialized  
#define ERR_IS_INITIALIZED                  (DEVICE_ERR-7)     ///< Device is initialized  
#define ERR_DEVICE_BUSY                     (DEVICE_ERR-8)     ///< Another thread is currently using device functions
#define ERR_NO_HARDWARE_SUPPORT             (DEVICE_ERR-9)     ///< No hardware support for requested function 
#define ERR_DEVICE_READ_PARAM               (DEVICE_ERR-10)    ///< Device parameters can't be read
#define ERR_DEVICE_WRITE_PARAM              (DEVICE_ERR-11)    ///< Parameter write to device failed
#define ERR_DEVICE_INVALID_PARAM            (DEVICE_ERR-12)    ///< Parameter read from device is invalid
#define ERR_DEVICE_INSUFFICIENT_MEMORY      (DEVICE_ERR-13)    ///< No memory available for specified action (exceeded size)
#define ERR_DEVICE_WRONG_OPERATION_MODE     (DEVICE_ERR-14)    ///< Device operation mode is incorrect
#define ERR_IS_CAPTUREING                   (DEVICE_ERR-15)    ///< Device is capturing
#define ERR_DEVICE_NO_SUPPORT               (DEVICE_ERR-16)    ///< Device is no support

#define ERR_DEVICE_EXCEED_MAX               (DEVICE_ERR-17)    ///< To exceed the maximum of device number.
#define ERR_HANDLE_INVALID                  (DEVICE_ERR-18)    ///< Invalid handle for device
#define ERR_HANDLE_NOT_MATCH                (DEVICE_ERR-19)    ///< Input handle and current handle not match
#define ERR_AUTO_CAP_AREA_INFO              (DEVICE_ERR-20)    ///< Input auto capture area information error
#define ERR_NOT_CAPTURING                   (DEVICE_ERR-21)    ///< No capture is running
#define ERR_CAPTURE_PALMMOVING              (DEVICE_ERR-22)    ///< Palm is Moving

#define ERR_CONTROL_STREAM                  (DEVICE_ERR-23)    ///< Control stream failed
#define ERR_STILL_INFORMATION_SET           (DEVICE_ERR-24)    ///< Set still stream information failed
#define ERR_STUFF_AND_RUN_STREAM            (DEVICE_ERR-25)    ///< Stuff and run stream failed
#define ERR_SET_VIDEO_PROP                  (DEVICE_ERR-26)    ///< Set video property failed
#define ERR_SET_EXPOSURE_FAILED             (DEVICE_ERR-27)    ///< Set exposure failed
#define ERR_SETUP_DI_ENUM_DEVICE_INFO       (DEVICE_ERR-28)    ///< Setup DiEnum device information failed
#define ERR_USB_VERSION_NO_SUPPORT          (DEVICE_ERR-29)    ///< USB version is no support
#define ERR_ENTRY_POINT_INVALID             (DEVICE_ERR-30)    ///< Invalid entry point

    // special error codes
#define SPECIAL_ERR                          (-800)
#define ERR_SPECIAL_InvalidInputParameters   (SPECIAL_ERR-1)     ///< Invalid Input Parameters
#define ERR_SPECIAL_InvalidInputParameters1  (SPECIAL_ERR-2)     ///< Invalid Input Parameters1
#define ERR_SPECIAL_InvalidInputParameters2  (SPECIAL_ERR-3)     ///< Invalid Input Parameters2
#define ERR_SPECIAL_InvalidInputParameters3  (SPECIAL_ERR-4)     ///< Invalid Input Parameters3
#define ERR_SPECIAL_InvalidInputParameters4  (SPECIAL_ERR-5)     ///< Invalid Input Parameters4
#define ERR_SPECIAL_InvalidInputParameters5  (SPECIAL_ERR-6)     ///< Invalid Input Parameters5
#define ERR_SPECIAL_InvalidInputParameters6  (SPECIAL_ERR-7)     ///< Invalid Input Parameters6
#define ERR_SPECIAL_InvalidInputParameters7  (SPECIAL_ERR-8)     ///< Invalid Input Parameters7
#define ERR_SPECIAL_InvalidInputParameters8  (SPECIAL_ERR-9)     ///< Invalid Input Parameters8
#define ERR_SPECIAL_InvalidInputParameters9  (SPECIAL_ERR-10)    ///< Invalid Input Parameters9
#define ERR_SPECIAL_InvalidInputPointer      (SPECIAL_ERR-11)    ///< Invalid Input Pointer
#define ERR_SPECIAL_CannotAllocateMemory     (SPECIAL_ERR-12)    ///< Can't Allocate Memory
#define ERR_SPECIAL_CannotOpenFile           (SPECIAL_ERR-13)    ///< Can't Open File
#define ERR_SPECIAL_CannotOpenImageFile      (SPECIAL_ERR-14)    ///< Can't Open Image File
#define ERR_SPECIAL_CannotReadImageData      (SPECIAL_ERR-15)    ///< Can't Read Image Data
#define ERR_SPECIAL_CannotOpenCaptureDevice  (SPECIAL_ERR-16)    ///< Can't Open Capture Device, Please connect the fingerprint sensor to your computer or check whether its driver is installed
#define ERR_SPECIAL_DirtySensorWindow        (SPECIAL_ERR-17)    ///< The sensor window might be dirty, please clean it before you capture fingerprints
#define ERR_SPECIAL_LowContrast              (SPECIAL_ERR-18)    ///< The sensor might be Low Contrast Please calibrate it
#define ERR_SPECIAL_LowExplosure             (SPECIAL_ERR-19)    ///< The sensor might be Low Exposure Please calibrate it
#define ERR_SPECIAL_LowBrightness            (SPECIAL_ERR-20)    ///< The sensor might be Low Exposure Please calibrate it
#define ERR_SPECIAL_TooWhite                 (SPECIAL_ERR-21)    ///< If you have placed your finger quite hard on the sensor, then the brightness of the sensor might be too big or the contrast is too low
#define ERR_SPECIAL_TooDark                  (SPECIAL_ERR-22)    ///< The brightness of the sensor might be too small
#define ERR_SPECIAL_SmallDynamicRange        (SPECIAL_ERR-23)    ///< If you have placed your finger quite hard on the sensor, then the contrast of the sensor is too low
#define ERR_SPECIAL_SmallVar                 (SPECIAL_ERR-24)    ///< If you have placed your finger quite hard on the sensor, then the contrast of the sensor is too low
#define ERR_SPECIAL_TooFast                  (SPECIAL_ERR-25)    ///< Your rolling speed is too fast, please try pressing harder and rolling a little more slowly
#define ERR_SPECIAL_TooSlow                  (SPECIAL_ERR-26)    ///< Your rolling speed is too slow, please try rolling a little more faster
#define ERR_SPECIAL_RollBack                 (SPECIAL_ERR-27)    ///< Don't leave or roll backwards until you finish rolling all area of your finger
#define ERR_SPECIAL_Sliding                  (SPECIAL_ERR-28)    ///< Don't slide your finger during rolling
#define ERR_SPECIAL_ImageForeGoundTooSmall              (SPECIAL_ERR-29)     ///< image foreGound too small
#define ERR_SPECIAL_ForeGoundWidthTooSmall              (SPECIAL_ERR-30)     ///< Foreground Width Too Small, please roll a little faster
#define ERR_SPECIAL_ForeGoundHeightTooSmall             (SPECIAL_ERR-31)     ///< Foreground Height Too Small
#define ERR_SPECIAL_ForeGoundWidthTooSmallEarlyAbort    (SPECIAL_ERR-32)     ///< ForeGound Width Too Small because your finger left, rolled backwards or slide before complete fingerprint is sampled
#define ERR_SPECIAL_ImageCenterTooLow                   (SPECIAL_ERR-33)     ///< Image Center Too Low,please place your finger a little higher
#define ERR_SPECIAL_ImageCenterTooHigh                  (SPECIAL_ERR-34)     ///< Image Center Too High, please place your finger a little Lower
#define ERR_SPECIAL_ImageQualityTooLow                  (SPECIAL_ERR-35)     ///< Image Quality Too Low
#define ERR_SPECIAL_DryFinger                                    (SPECIAL_ERR-36)     ///< Dry finger Please press harder or Calibrate the sensor with Lower sensor brightness and higher contrast
#define ERR_SPECIAL_WetFinger                                    (SPECIAL_ERR-37)     ///< Wet finger Please press slighter or Calibrate the sensor Higher sensor brightness and higher contrast
#define ERR_SPECIAL_DirtySensorWindow1                           (SPECIAL_ERR-38)     ///< If your finger is on the sensor, please remove it from the sensor
#define ERR_SPECIAL_FingerIsLeaving                              (SPECIAL_ERR-39)     ///< Your finger is leaving
#define ERR_SPECIAL_Saturated                                    (SPECIAL_ERR-40)     ///< Saturated
#define ERR_SPECIAL_TooManyDefectedLines                         (SPECIAL_ERR-41)     ///< Too Many Defected Lines

    // Macros
#define MAX_STR_LEN                 128                 ///< Required buffer length for string parameters

    // Command mask bit constants 
#define CMD_MASK                    0x0000              ///< NULL command mask
#define CMD_MASK_HALO               0x0001              ///< Remove halo command mask
#define CMD_MASK_FAKE_DETECTION     0x0002              ///< Fake detection command mask


    ////////////////////////////////////////////////////////////////////////////////
    // struct & enum
    typedef enum tagLEDColor
    {
        LED_COLOR_RED,                                ///< Gray scale image
        LED_COLOR_GREEN,                               ///< 24 bit RGB color image
        LED_COLOR_BLUE,                                ///< True color RGB image
        LED_COLOR_OFF
    } LEDColor;

    /// Image format constants.
    typedef enum tagImageFormat
    {
        IMG_FORMAT_GRAY,                                ///< Gray scale image
        IMG_FORMAT_RGB24,                               ///< 24 bit RGB color image
        IMG_FORMAT_RGB32                                ///< True color RGB image
    } ImageFormat;

    /// Container to hold image data together with meta information.
    typedef struct tagImageData
    {
        void* Buffer;                       ///< Pointer to image buffer
        DWORD             Width;                        ///< Image horizontal size
        DWORD             Height;                       ///< Image vertical size
        double            ResolutionX;                  ///< Horizontal image resolution (in PPI)
        double            ResolutionY;                  ///< Vertical image resolution (in PPI)
        double            FrameTime;                    ///< Image acquisition time (in seconds)\n
        ///< This value contains the time taken for acquisition
        ///< from device (without processing time).
        int               Pitch;                        ///< Image line pitch (in Bytes).\n
        ///  Positive values indicate top down line order,
        ///  Negative values mean bottom up line order
        BYTE              BitsPerPixel;                 ///< Number of Bits per pixel
        ImageFormat       Format;                       ///< Image color format
        BOOL              IsFinal;                      ///< Marks image as finally processed\n
        ///  A value of "FALSE" disqualifies image for further processing.
        ///  (e.g. interim or preprocessed result images)
    } ImageData;

    /// Container to hold version information.
    typedef struct tagDTFApiVersion
    {
        char Product[MAX_STR_LEN];                  ///< Product version string
        char SdkVer[MAX_STR_LEN];                   ///< SDK version string
        char DllVer[MAX_STR_LEN];                ///< DLL version string
    } DTFApiVersion;

    /// Device property information.
    typedef struct tagDTFPropertyInfo
    {
        int  nResolution;                               ///< 500 or 1000 ppi
        char szMaker[MAX_STR_LEN];                  ///< Device Maker
        char szModel[MAX_STR_LEN];                  ///< Device model type
        char szInterfaceType[MAX_STR_LEN];          ///< Device interface type (USB, FireWire)
        char szSerial[MAX_STR_LEN];                 ///< Device serial no
        char szVer[MAX_STR_LEN];                    ///< Firmware version of scanner
        char szManDate[MAX_STR_LEN];                ///< Manufacture date
        char szServDate[MAX_STR_LEN];               ///< Last service date
    } DTFPropertyInfo;

    // Device running information.
    typedef struct tagDTFRunningInfo
    {
        BOOL bIsInitialized;                            ///< Flag to Initialized
        BOOL bIsCaptueing;                              ///< Flag to Capturing
        BOOL bIsCaptureAbort;                           ///< Flag to Capture abort
        BOOL bAutoCapture;                              ///< Flag to auto capture
        BOOL bAutoContrast;                             ///< Flag to auto contrast
        BOOL bStartPreview;                             ///< Flag to start preview
        BOOL bIsCaptureOK;                              ///< Flag to capture OK
        BOOL bIsStartRolling;                           ///< Flag to start rolling
        int  nErrorCode;                                ///< Error code
    } DTFRunningInfo;

    // Connected scanner
    typedef struct tagDTFScannerExist
    {
        int  nDevConnected; ///< connected scanner count
        BOOL b200;
        BOOL b500;		///< Flag to scanner type
    } DTFScannerExist;

    // Auto capture information
    typedef struct tagDTFAutoCapInfo {
        int   nLiveRes;                 ///< The resolution of Live image
        int nAutoCap_GreyLevel;         ///< This item control the minimum average grey level for each fingerprint block.(the default value is 230)
        double dAutoCap_SquarePecent;   ///< This item means how many percentage over the whole capture screen(the default value is 2.0)
        int nAutoCap_Qua;               ///< This item control the fingerprint quality(the default value is 12)
        int nAutoCap_NoMoveFrames;      ///< This item means how many still frames need to be detected before trigger(the default value is 3)
        int nAutoCap_MaxDevCentX;       ///< This item control the fingerprint center, X-axis coordinates(the default value is 10)
        int nAutoCap_MaxDevCentY;       ///< This item control the fingerprint center, Y-axis coordinates(the default value is 10)
        int nAutoCap_MaxDevGrey;        ///< This item control the fingerprint gray level(the default value is 15)
        int nAutoCap_MaxDevSquare;      ///< This item control the fingerprint area shift between two continuous image frames(the default value is 3000)
    } DTFAutoCapInfo;

    // Roll construct parameters
#ifndef DF_ROLL_PARAMETERS
#define DF_ROLL_PARAMETERS
    typedef struct tagDFRollParameters
    {
        //int   ScannerType;

        int   MaxFrameNumber;                           ///< The maximum number of frames used to stitch a image
        int   SlideDetectionStatus;                     ///< =1 enable the slide detection function, else disable
        int   SlidingPixelCounter;                      ///< The number of pixel is considered to be sliding comparing to the previous frame
                                                        ///< The smaller SlidingPixelCounter, the more sensitive to detect sliding and rotation
                                                        ///< good value = 8000, general value = 25000, low value = 31000
        float SlidingPercentageThreshold;               ///< The threshold of percentage of sliding pixel to total pixel number
                                                        ///< The smaller SlidingPercentageThreshold, the more sensitive to detect sliding and rotation
                                                        ///< SlidingPercentageThreshold must within [0.0, 1.0]
                                                        ///< good value = 0.157, general value = 0.202, low value = 0.26
        int   SlidingSADMeanThreshlod;                  ///< A measure to judge whether a pixel is sliding 
                                                        ///< if the SADMean of a pixel is greater than SlidingSADMeanThreshlod, it might be silding
                                                        ///< good value = 34, general value = 36, low value = 38
        int   RollBackThreshold;                        ///< The greater RollBackThreshold, the more sensitive to detect Roll Back
                                                        ///< RollBackThreshold must < 0
                                                        ///< good value = -200, general value = -300, low value = -400
        int   CheckSensorThreshold;                     ///< The smaller CheckSensorThreshold, the more sensitive to detect Sensor
                                                        ///< good value = 255, general value = 500, low value = 1000
    } DFRollParameters;
#endif

    /// Image types.
    /// They are used as parameter for @ref Capture_SetMode
    typedef enum tagDTFImageType
    {
        ROLL_SINGLE_FINGER,                         ///< Rolled finger print image 
        FLAT_SINGLE_FINGER,                         ///< Flat single finger
        FLAT_RIGHT_FINGERS,                         ///< Right flat fingers
        FLAT_LEFT_FINGERS,                          ///< Left flat fingers
        FLAT_TWO_THUMBS,                            ///< Two flat thumbs
        ROLL_RIGHT_THUMB,                           ///< Right thumb Rolled finger print image
        ROLL_LEFT_THUMB,                            ///< Left thumb Rolled finger print image

        PALM_RIGHT_FULL,                            ///< Full right palm
        PALM_RIGHT_WRITERS,                         ///< Right writers palm
        PALM_RIGHT_LOWER,                           ///< Right lower palm
        PALM_RIGHT_UPPER,                           ///< Right upper palm
        PALM_LEFT_FULL,                             ///< Full left palm
        PALM_LEFT_WRITERS,                          ///< Left writers palm
        PALM_LEFT_LOWER,                            ///< Left lower palm
        PALM_LEFT_UPPER,                            ///< Left upper palm

        ROLL_RIGHT_INDEX,                           ///< Right index Rolled finger print image
        ROLL_RIGHT_MIDDLE,                          ///< Right middle Rolled finger print image
        ROLL_RIGHT_RING,                            ///< Right ring Rolled finger print image
        ROLL_RIGHT_SMALL,                           ///< Right small Rolled finger print image
        ROLL_LEFT_INDEX,                            ///< Left index Rolled finger print image
        ROLL_LEFT_MIDDLE,                           ///< Left middle Rolled finger print image
        ROLL_LEFT_RING,                             ///< Left ring Rolled finger print image
        ROLL_LEFT_SMALL,                            ///< Left small Rolled finger print image

        FLAT_RIGHT_THUMB,                           ///< Right flat thumb
        FLAT_RIGHT_INDEX,                           ///< Right flat index
        FLAT_RIGHT_MIDDLE,                          ///< Right flat middle
        FLAT_RIGHT_RING,                            ///< Right flat ring
        FLAT_RIGHT_SMALL,                           ///< Right flat small
        FLAT_LEFT_THUMB,                            ///< Left flat thumb
        FLAT_LEFT_INDEX,                            ///< Left flat index
        FLAT_LEFT_MIDDLE,                           ///< Left flat middle
        FLAT_LEFT_RING,                             ///< Left flat ring
        FLAT_LEFT_SMALL,                            ///< Left flat small

        // For two finger (TBD:)
        FLAT_TWO_THUMBS_R_IndexMiddle,
        FLAT_TWO_THUMBS_R_RingSmall,
        FLAT_TWO_THUMBS_L_IndexMiddle,
        FLAT_TWO_THUMBS_L_RingSmall,

        FLAT_ALL_FINGERS,
        TYPE_NONE,                                  ///< No image (default after initialization)
    } DTFImageType;

    /// Image resolution types.
    /// They are used as parameter for @ref LSCAN_Capture_SetMode
    typedef enum tagDTFImageResolution
    {
        IMAGE_RESOLUTION_500 = 500,                ///< 500ppi
        IMAGE_RESOLUTION_1000 = 1000                ///< 1000ppi
    } DTFImageResolution;

    /// LED field types.
    typedef enum tagDTFLedType
    {
        LED_FINGER,                                 ///< LEDs to indicate finger LEDs
        LED_STATUS,                                 ///< LEDs to indicate status LEDs
        LED_EXTEND,                                 ///< LEDs to indicate extend LEDs
        LED_NONE                                    ///< no LED field available
    } DTFLedType;

    /// Quality state definitions for detected finger/hand.
    typedef enum tagDTFObjectQualityState
    {
        OBJECT_NOT_PRESENT,                         ///< Object not detected
        OBJECT_GOOD,                                ///< Object tracking OK
        OBJECT_TOO_LIGHT,                           ///< Object contrast too low
        OBJECT_TOO_DARK,                            ///< Object contrast too dark
        OBJECT_BAD_SHAPE,                           ///< Object shape not OK
        OBJECT_POSITION_NOT_OK,                     ///< Object position not within tracking area
        OBJECT_POSITION_TOO_LEFT,                   ///< Object position too left
        OBJECT_POSITION_TOO_RIGHT,                  ///< Object position too right
        OBJECT_POSITION_TOO_TOP,                   ///< Object position too top
        OBJECT_CORE_NOT_PRESENT,                    ///< Object core not found
        OBJECT_TRACKING_NOT_OK                      ///< Required tracking time has not been reached yet
    } DTFObjectQualityState;

    /// Object/Finger count state definitions.
    typedef enum tagDTFObjectCountState
    {
        OBJECT_COUNT_OK,                            ///< Object count is OK.
        TOO_MANY_OBJECTS,                           ///< Object count is too many objects.
        TOO_FEW_OBJECTS                             ///< Object count is too few objects.
    } DTFObjectCountState;

    /// Keypad types.
    typedef enum tagDTFKeypadType
    {
        KEYPAD_C_KEYS,                              ///< Keypad 'C' button
        KEYPAD_D_KEYS,                              ///< Keypad 'D' button
        KEYPAD_NONE                                 ///< No keypad available
    } DTFKeypadType;

    // Scanner type
    typedef enum tagDTFScannerType
    {
        SCANNER_ONE_FINGER = 300,
        SCANNER_DF200 = SCANNER_ONE_FINGER + 3,

        SCANNER_TWO_FINGER = 400,

        SCANNER_FOUR_FINGER = 500,
        SCANNER_DF500 = SCANNER_FOUR_FINGER + 4,

        SCANNER_PALM = 600,

        // ...
        SCANNER_PENDING = 800,

        SCANNER_NULL = -1
    } DTFScannerType;

    //single fingerprint data
    typedef struct SegFPData_t
    {
        int nFGP;   //从右至左 1-10
        int nWidth;
        int nHeight;
        int nQuality;  //一般15，小于12质量差
        int nRawImgLen;
        unsigned char* pucRawImg;
    } SegFPData;
    ////////////////////////////////////////////////////////////////////////////////
    // Interface

    //------------------------------------------------------------------- 
    // Function name: Main_GetConnectedScanner
    // Parameter:
    //    input:  
    //    output: 
    //    in/out: scannerExist - connected scanner; memory provided by caller!
    // Return:
    //    STATUS_OK
    //    ERR_INVALID_PARAM_VALUE
    // Description: Get connected scanner.
    //------------------------------------------------------------------- 
    int WINAPI Main_GetConnectedScanner(DTFScannerExist* scannerExist);

    //------------------------------------------------------------------- 
    // Function name: Main_GetAPIVersion
    // Parameter:
    //    input:  
    //    output: 
    //    in/out: info - API version information; memory provided by caller!
    // Return:
    //    STATUS_OK
    //    ERR_INVALID_PARAM_VALUE
    // Description: Get DLL version information.
    //------------------------------------------------------------------- 
    int WINAPI Main_GetAPIVersion(DTFApiVersion* info);

    //------------------------------------------------------------------- 
    // Function name: Main_GetRunningInfo
    // Parameter:
    //    input:  
    //    output: 
    //    in/out: info - Device running information; memory provided by caller!
    // Return:
    //    STATUS_OK
    //    ERR_INVALID_PARAM_VALUE
    // Description: Get Running information.
    //------------------------------------------------------------------- 
    int WINAPI Main_GetRunningInfo(DTFRunningInfo* info);

    //------------------------------------------------------------------- 
    // Function name: Main_Initialize
    // Parameter:
    //    input:  ScannerType - scanner type; default value is DF_SCANNER_CS500I
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_IS_INITIALIZED
    //    ERR_DEVICE_IO
    // Description: Initialize scanner.
    //------------------------------------------------------------------- 
    int WINAPI Main_Initialize(DTFScannerType ScannerType = SCANNER_DF500);

    //------------------------------------------------------------------- 
    // Function name: Main_DeInitialize
    // Parameter:
    //    input:  
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    // Description: DeInitialize scanner.
    //------------------------------------------------------------------- 
    int WINAPI Main_DeInitialize();

    //------------------------------------------------------------------- 
    // Function name: Main_FastStartup
    // Parameter:
    //    input:  ScannerType - scanner type; default value is DF_SCANNER_CS500I
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    // Description: Fast Startup scanner.
    //------------------------------------------------------------------- 
    int WINAPI Main_FastStartup(DTFScannerType ScannerType = SCANNER_DF500);

    //------------------------------------------------------------------- 
    // Function name: Main_StandBy
    // Parameter:
    //    input:  
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    // Description: StandBy scanner.
    //------------------------------------------------------------------- 
    int WINAPI Main_StandBy();

    //------------------------------------------------------------------- 
    // Function name: Main_GetDeviceInfo
    // Parameter:
    //    input:  
    //    output: 
    //    in/out: info - Basic device information; memory provided by caller!
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Retrieve detailed device information.
    //------------------------------------------------------------------- 
    int WINAPI Main_GetDeviceInfo(DTFPropertyInfo* info);

    //------------------------------------------------------------------- 
    // Function name: Capture_SetMode
    // Parameter:
    //    input:  imageType - Image type to capture
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
    //              This function needs to be called prior to CAPTURE_Start().
    //------------------------------------------------------------------- 
    int WINAPI Capture_SetMode(
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
    // Function name: Capture_Start
    // Parameter:
    //    input:  numberOfObjects - Number of expected fingertips in the image
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
    int WINAPI Capture_Start(const int  numberOfObjects, BOOL AutoAcquireResultImage = TRUE);

    //------------------------------------------------------------------- 
    // Function name: Capture_Abort
    // Parameter:
    //    input:  
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    // Description: Abort running image acquisition.
    //------------------------------------------------------------------- 
    int WINAPI Capture_Abort();

    //------------------------------------------------------------------- 
    // Function name: Capture_TakeResultImage
    // Parameter:
    //    input:  
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    // Description: Initiate manual result image acquisition.
    //              This function needs to be called prior to Capture_AcquireResultImage().
    //------------------------------------------------------------------- 
    int WINAPI Capture_TakeResultImage();

    //------------------------------------------------------------------- 
    // Function name: Capture_AcquireResultImage
    // Parameter:
    //    input:  
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    // Description: Acquire the result image, it might take several seconds, expect a delay
    //------------------------------------------------------------------- 
    int WINAPI Capture_AcquireResultImage();

    //------------------------------------------------------------------- 
    // Function name: Capture_GetContrast
    // Parameter:
    //    input:  
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Get contrast value for selected capture mode selected by Capture_SetMode().
    //------------------------------------------------------------------- 
    //int WINAPI Capture_GetContrast(int *contrastValue);

    //------------------------------------------------------------------- 
    // Function name: Capture_SetContrast
    // Parameter:
    //    input:  contrastValue - Contrast value 
    //                            (range: 0 <= value <= MAX_CONTRAST_VALUE)
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Set contrast value for selected capture mode selected by Capture_SetMode().
    //------------------------------------------------------------------- 
    //int WINAPI Capture_SetContrast(const int contrastValue);

    //------------------------------------------------------------------- 
    // Function name: Capture_OptimizeContrast
    // Parameter:
    //    input:  
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    // Description: Initiate manual contrast optimization.
    //------------------------------------------------------------------- 
    int WINAPI Capture_OptimizeContrast();

    //------------------------------------------------------------------- 
    // Function name: Controls_SetStateLEDs
    // Parameter:
    //    input:  CapTypeApi - Image type to active status LED's
    //            StateLEDs - show type of active LED's   
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Set active status LED's on device.
    //------------------------------------------------------------------- 
    int WINAPI Controls_SetStateLEDs(DTFImageType CapTypeApi, unsigned char* StateLEDs);

    //------------------------------------------------------------------- 
    // Function name: Controls_SetFingerLEDs
    // Parameter:
    //    input:  CapTypeApi - Image type to active status LED's
    //            iColor - show color of active LED's   
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Set active status LED's on device.
    //------------------------------------------------------------------- 
    int WINAPI Controls_SetFingerLEDs(DTFImageType CapTypeApi, LEDColor iColor);


    //------------------------------------------------------------------- 
    // Function name: Controls_SetLEDs
    // Parameter:
    //    input:  ledType - show type of active LED's
    //            ledValue - Led's value
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Set active LED's on device.
    //------------------------------------------------------------------- 
    int WINAPI Controls_SetLEDs(DTFLedType ledType, int ledValue);

    //------------------------------------------------------------------- 
    // Function name: Controls_GetLEDs
    // Parameter:
    //    input:  ledType - show type of active LED's
    //            ledValue - Led's value
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Set active LED's on device.
    //------------------------------------------------------------------- 
    int WINAPI Controls_GetLEDs(DTFLedType ledType, int* ledValue);

    //------------------------------------------------------------------- 
    // Function name: Controls_Beeper
    // Parameter:
    //    input:  BeepMode - Beeper mode
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_NOT_SUPPORTED
    // Description: Send beep pattern to internal device beeper.
    //------------------------------------------------------------------- 
    int WINAPI Controls_Beeper(int BeepMode);

    //------------------------------------------------------------------- 
    // Function name: Capture_SetCaptureOK
    // Parameter:
    //    input:  
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    // Description: Set captured flag is OK.
    //------------------------------------------------------------------- 
    int WINAPI Capture_SetCaptureOK();

    //------------------------------------------------------------------- 
    // Function name: Capture_SetStartRollingFlag
    // Parameter:
    //    input:  flag - Flag to start rolling
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    // Description: Set start rolling flag.
    //------------------------------------------------------------------- 
    int WINAPI Capture_SetStartRollingFlag(BOOL flag);

    //------------------------------------------------------------------- 
    // Function name: Capture_GetRollParameters
    // Parameter:
    //    input:  
    //    output: 
    //    in/out: para - Roll construct parameters; memory provided by caller!
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Get roll parameters.
    //------------------------------------------------------------------- 
    int WINAPI Capture_GetRollParameters(DFRollParameters* para);

    //------------------------------------------------------------------- 
    // Function name: Capture_SetRollParmeters
    // Parameter:
    //    input:  para - Roll construct parameters;
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Set roll parameters.
    //------------------------------------------------------------------- 
    int WINAPI Capture_SetRollParameters(DFRollParameters para);

    //------------------------------------------------------------------- 
    // Function name: Capture_Calibration
    // Parameter:
    //    input:  
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_MEM_ALLOC
    //    ERR_COMMAND_FAILED
    // Description: Calibrate scanner.
    //------------------------------------------------------------------- 
    int WINAPI Capture_Calibration();

    //------------------------------------------------------------------- 
    // Function name: Controls_RegisterFootSwitchInfo
    // Parameter:
    //    input:  hWnd - windows handler to display live image
    //            Msg - footswitch message id
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    // Description: Register Footswitch information.
    //------------------------------------------------------------------- 
    int WINAPI Controls_RegisterFootSwitchInfo(HWND hWnd, UINT Msg);

    //------------------------------------------------------------------- 
    // Function name: CallbackPreviewImage
    // Parameter:
    //    input:  pContext - caller defined context (e.g. handler object instance pointer)
    //            image - preview image (valid until callback function is exited)
    //    output: 
    //    in/out:
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Preview image available notification.
    //------------------------------------------------------------------- 
    typedef void (CALLBACK* CallbackPreviewImage) (
        void* pContext,
        const ImageData image
        );

    //------------------------------------------------------------------- 
    // Function name: Capture_RegisterCallbackPreviewImage
    // Parameter:
    //    input:  callback - Pointer to the notification function 
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
    int WINAPI Capture_RegisterCallbackPreviewImage(
        CallbackPreviewImage   callback,
        void* context
    );

    //------------------------------------------------------------------- 
    // Function name: CallbackTakingResultImage
    // Parameter:
    //    input:  pContext - caller defined context (e.g. handler object instance pointer)
    //    output: 
    //    in/out:
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: This notification is sent to indicate begin of result image acquisition.
    //------------------------------------------------------------------- 
    typedef void (CALLBACK* CallbackTakingResultImage) (
        void* pContext
        );

    //------------------------------------------------------------------- 
    // Function name: Capture_RegisterCallbackTakingResultImage
    // Parameter:
    //    input:  callback - Pointer to the notification function 
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
    int WINAPI Capture_RegisterCallbackTakingResultImage(
        CallbackTakingResultImage   callback,
        void* context
    );

    //------------------------------------------------------------------- 
    // Function name: CallbackResultImage
    // Parameter:
    //    input:  pContext - caller defined context (e.g. handler object instance pointer)
    //            imageStatus - result image status value (value >= STATUS_OK indicates success)
    //            image - preview image (valid until callback function is exited)
    //            imageType - result image type (e.g. LSCAN_ROLL_SINGLE_FINGER)
    //            detectedObjects - number of detected objects/fingers in result image 
    //    output: 
    //    in/out:
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Result image acquisition completion notification.
    //              (only valid if imageStatus >= STATUS_OK) 
    //------------------------------------------------------------------- 
    typedef void (CALLBACK* CallbackResultImage) (
        void* pContext,
        const int            imageStatus,
        const ImageData      image,
        const DTFImageType   imageType,
        const int            detectedObjects
        );

    //------------------------------------------------------------------- 
    // Function name: Capture_RegisterCallbackResultImage
    // Parameter:
    //    input:  callback - Pointer to the notification function 
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
    int WINAPI Capture_RegisterCallbackResultImage(
        CallbackResultImage   callback,
        void* context
    );

    //------------------------------------------------------------------- 
    // Function name: CallbackFootSwitch
    // Parameter:
    //    input:  pContext - caller defined context (e.g. handler object instance pointer)
    //    output: 
    //    in/out:
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: This notification is sent to indicate message of trigger Footswitch.
    //------------------------------------------------------------------- 
    typedef void (CALLBACK* CallbackFootSwitch) (
        void* pContext
        );

    //------------------------------------------------------------------- 
    // Function name: Capture_RegisterCallbackFootSwitch
    // Parameter:
    //    input:  callback - Pointer to the notification function 
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
    int WINAPI Capture_RegisterCallbackFootSwitch(
        CallbackFootSwitch  callback,
        void* context
    );

    //------------------------------------------------------------------- 
    // Function name: CallbackKeypad
    // Parameter:
    //    input:  pContext - caller defined context (e.g. handler object instance pointer)
    //            keypadType - current key type
    //    output: 
    //    in/out:
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: This notification is sent to indicate message of trigger Keypad.
    //------------------------------------------------------------------- 
    typedef void (CALLBACK* CallbackKeypad) (
        void* pContext,
        const DTFKeypadType     keypadType
        );

    //------------------------------------------------------------------- 
    // Function name: Capture_RegisterCallbackKeypad
    // Parameter:
    //    input:  callback - Pointer to the notification function 
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
    int WINAPI Capture_RegisterCallbackKeypad(
        CallbackKeypad      callback,
        void* context
    );

    //------------------------------------------------------------------- 
    // Function name: CallbackObjectQuality
    // Parameter:
    //    input:  pContext - caller defined context (e.g. handler object instance pointer)
    //            fingerCountState - finger count state (OK, too few, too many)
    //            pQualityArray - pointer to an array of finger tip quality states (array size in quality count)
    //            qualityCount - size of finger tip quality array
    //    output: 
    //    in/out:
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Finger tip quality change notification.
    //------------------------------------------------------------------- 
    typedef void (CALLBACK* CallbackObjectQuality) (
        void* pContext,
        const DTFObjectCountState   fingerCountState,
        const DTFObjectQualityState* pQualityArray,
        const int                   qualityCount
        );

    //------------------------------------------------------------------- 
    // Function name: Capture_RegisterCallbackObjectQuality
    // Parameter:
    //    input:  callback - Pointer to the notification function 
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
    int WINAPI Capture_RegisterCallbackObjectQuality(
        CallbackObjectQuality   callback,
        void* context
    );

    //------------------------------------------------------------------- 
    // Function name: CallbackDeviceIsConnected
    // Parameter:
    //    input:  pContext - caller defined context (e.g. handler object instance pointer)
    //            bIsExist - the current equipment is exist, isn't?
    //    output: 
    //    in/out:
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Is connected the current device?
    //------------------------------------------------------------------- 
    typedef void (CALLBACK* CallbackDeviceIsConnected) (
        void* pContext,
        const BOOL                  bIsExist
        );

    //------------------------------------------------------------------- 
    // Function name: Capture_RegisterCallbackDeviceIsConnected
    // Parameter:
    //    input:  callback - Pointer to the notification function 
    //            context - Pointer to user context; this value is used 
    //                      as parameter for callback
    //    output: 
    //    in/out:
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Register callback function for the current equipment is connected.
    //------------------------------------------------------------------- 
    int WINAPI Capture_RegisterCallbackDeviceIsConnected(
        CallbackDeviceIsConnected  callback,
        void* context
    );

    //------------------------------------------------------------------- 
    // Function name: Capture_GetImageMask
    // Parameter:
    //    input:  
    //    output: 
    //    in/out: pImageMask - Rolling mask image; memory provided by caller!
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Get rolling mask image.
    //------------------------------------------------------------------- 
    int WINAPI Capture_GetImageMask(
        unsigned char* pImageMask
    );

    //------------------------------------------------------------------- 
    // Function name: Capture_SetAutoCapInfo
    // Parameter:
    //    input:  para - Auto capture information
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    // Description: Set auto capture information.
    //------------------------------------------------------------------- 
    int WINAPI Capture_SetAutoCapInfo(
        DTFAutoCapInfo para
    );

    //------------------------------------------------------------------- 
    // Function name: Capture_SetAutoCapInfo
    // Parameter:
    //    input:  bAutoCapArea - auto capture area flag
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
    int WINAPI Capture_SetAutoCapArea(BOOL bAutoCapArea, int xPos = 0, int yPos = 0, int width = 0, int height = 0);

    //------------------------------------------------------------------- 
    // Function name: Capture_SetAutoCapFinMask
    // Parameter:
    //    input:  nFinMask - finger mask.
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Set auto capture finger mask.
    //------------------------------------------------------------------- 
    int WINAPI Capture_SetAutoCapFinMask(int nFinMask);

    //------------------------------------------------------------------- 
    // Function name: Control_CmdSetValue
    // Parameter:
    //    input:  dwCommandMask - command mask.
    //    output: 
    //    in/out: 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Set command mask.
    //------------------------------------------------------------------- 
    int WINAPI Control_CmdSetValue(DWORD dwCommandMask = CMD_MASK);

    //------------------------------------------------------------------- 
    // Function name: CallbackSensorIsDirty
    // Parameter:
    //    input:  pContext - caller defined context (e.g. handler object instance pointer)
    //            nDirtyFlag - denote if the sensor surface is dirty. 0 means clean surface, 1 means dirty surface
    //    output: 
    //    in/out:
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Preview image available notification.
    //------------------------------------------------------------------- 
    typedef void (CALLBACK* CallbackSensorIsDirty) (
        void* pContext,
        const int		nDirtyFlag
        );

    //------------------------------------------------------------------- 
    // Function name: Capture_RegisterCallbackSensorIsDirty
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
    int WINAPI Capture_RegisterCallbackSensorIsDirty(
        CallbackSensorIsDirty   callback,
        void* context
    );

    // a.b
    int WINAPI Capture_SaveRollingFrame();

    //------------------ Only for DEMO_TEST project ------------------
    int WINAPI LateralCutAdjust();
    int WINAPI Set_VideoProp(int VideoID, int Value);
    int WINAPI Set_DirtyCheckThreshold(double DirtyVarThreshA, double FingerVarThreshA, double DirtyVarThreshB, double FingerVarThreshB);

    //add hw ********All of the following*******************************************************************
    //------------------------------------------------------------------- 
    // Function name: Control_RemoveFog
    // Parameter:
    //    input:  Remove fog flag 
    // Return:
    //    STATUS_OK
    //    ERR_NOT_INITIALIZED
    //    ERR_INVALID_PARAM_VALUE
    // Description: Setting a flag of remove fog from image
    //------------------------------------------------------------------- 
    int WINAPI Control_RemoveFog(BOOL bFlag);


    //------------------------------------------------------------------- 
    // Function name: Capture_FPSegment
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
    int WINAPI Capture_FPSegment(
        const DTFImageType          imageType,
        BYTE* pRawImg,
        int							iWidth,
        int							iHeight,
        SegFPData* pSegFPData,
        int* NumSegFinger,
        char* pszErrMsg
    );

    int WINAPI Capture_Raw2Wsq(
        int nHeight,
        int nWidth,
        int nBitsCount,
        UCHAR* pucRawBuf,
        int* pnWSQBufLen,
        UCHAR** ppucWSQBuf,
        float fRatio
    );
    int WINAPI Capture_GetTemplate(
        unsigned char* Image,
        int ImgWidth,
        int ImgHeight,
        int FingerPosition,
        int TemplateType,
        unsigned char** Template,
        int* TemplateSize);

    int WINAPI Capture_IsTrueFinger(
        unsigned char* Image,
        int             iWidth,
        int             iHeight
    );


#ifdef __cplusplus
} // extern "C"
#endif

#endif    // __ESSENTIALS_API_H__

////////////////////////////////////////////////////////////////////////////////

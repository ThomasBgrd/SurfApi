//**************************************************************************//
//                                                                          //
//  File: SurfAPI.h                                                         //
//  Creation date: 09/feb/2001 16:05:34                                     //
//  Author: JVL                                                             //
//  Description: Surf API supporting                                        //
//                - Surf files version 1                                    //
//                - Surf files version 2                                    //
//                                                                          //
//**************************************************************************//

#ifndef _SurfAPI_h
#define _SurfAPI_h

#ifdef __cplusplus
extern "C" {
#endif

// définit le numéro de version
#define SURF_API_VER    0x01600000L  // v1.60


// packing
#pragma pack( push, SurfPack )
#pragma pack( 1 )


#if !defined(byte)
typedef unsigned char byte;
#endif // byte

#if !defined(BOOL)
typedef int BOOL;
#endif // BOOL

#if !defined(TRUE)
#define TRUE    ((int) 1)
#endif // TRUE

#if !defined(FALSE)
#define FALSE   ((int) 0)
#endif // FALSE


// supported studiable types
enum DSSTUDIABLE
{
  kdsUnknown                        = -1,

  kdsFirstStudiable                 = 1,

  kdsProfile                        = 1,
  kdsSurface                        = 2,
  kdsBinaryImage                    = 3,
  kdsProfileSeries                  = 4,
  kdsSurfaceSeries                  = 5,
  kdsMeridianDisc                   = 6,
  kdsMultiLayerProfile              = 7,
  kdsMultiLayerSurface              = 8,
  
  kdsParallelDisc                   = 9,  // not yet implemented

  kdsIntensityImage                 = 10,
  kdsIntensitySurface               = 11,

  kdsRGBImage                       = 12,
  kdsRGBSurface                     = 13,

  kdsForceCurve                     = 14,
  kdsSeriesOfForceCurve             = 15,

  kdsRGBIntensitySurface            = 16,

  kdsParametricProfile              = 17,

  kdsRGBImagesSeries                = 18,

  kdsParametricSurface              = 19, // not yet implemented

  kdsSpectrum                       = 20,

  kdsHyperSpectral                  = 21,

  kdsRoundnessProfile               = 22, 
  kdsMultiRoundnessProfile          = 23, 
  kdsFlatnessProfile                = 24, 
  kdsMultiFlatnessProfile           = 25, 

  kdsForceVolume                    = 26,
  kdsForceVolumeSpringConst         = 27,
  kdsForceVolumeSensitivityConst    = 28,

  kdsCITSSpectrum                   = 29,
  kdsCITSCube                       = 30,

  kdsMultiHorizontalStraightnessProfile = 31, // not yet implemented
  kdsMultiVerticalStraightnessProfile = 32, // not yet implemented
  kdsHelicoidalRoundnessProfile     = 33, // not yet implemented
  kdsSpiralFlatnessProfile          = 34, // not yet implemented

  kdsParametricForceCurve           = 35,
  kdsSeriesOfParametricForceCurve   = 36,
  kdsParametricForceVolume          = 37,

  kdsCloudParametricSurface         = 38, // not yet implemented
  kdsMultiChannelImage              = 39,
  kdsMultiChannelVolume             = 40, // not yet implemented

  kdsLastStudiable                  = kdsMultiChannelVolume
};
typedef enum DSSTUDIABLE DSSTUDIABLE;

// supported formats
enum DSFORMAT
{
  kFormatUnknown   = 0, // unknown format
  kFormatSurf1     = 1, // format Surf 1
  kFormatSurf2     = 2, // format Surf 2
  kFormatSDF       = 3, // format SDF

  kFormatCompressedSurf1 = 4, // format Surf 1, data compressed using zlib
};
typedef enum DSFORMAT DSFORMAT;


// flags used to open a file
enum DSFILEFLAGS
{
  kdsNoFile     = 0, // used for internal purpose

  kdsReadFile   = 1,
  kdsWriteFile  = 2
};
typedef enum DSFILEFLAGS DSFILEFLAGS;

// file handle
#ifndef _WIN64
typedef long  DSFILE;
#else
typedef __int64  DSFILE;
#endif

// error codes
enum DSRESULT 
{
  kdsOK                     =  1, // success !
  kdsError                  =  0, // generic error
  kdsInvalidFilename        = -1, // invalid filename
  kdsInvalidObject          = -2, // invalid object number
  kdsInvalidInfos           = -3, // structure infos
  kdsInvalidComment         = -4, // invalid comment
  kdsInvalidPoints          = -5, // invalid array of points
  kdsAlreadyOpen            = -6, // file already open
  kdsNotEnoughMemory        = -7, // not enough memory to run the operation
  kdsNotImplemented         = -8, // function not yet implemented
  kdsInvalidPointSize       = -9, // the size of the points is incorrect
  kdsInvalid1stArg          = -10, //
  kdsInvalid2ndArg          = -11, //
  kdsInvalid3rdArg          = -12, //
  kdsInvalid4thArg          = -13, //
  kdsUnknownStudiable       = -14, // invalid studiable type
  kdsWriteOnRead            = -15, // can't write in a file when open for reading
  kdsWrongObjectIndex       = -16, // the index of the object is not in the authorised range
  kdsWrongWriteOperation    = -17, // error in the order of the writing operations
  kdsIOFileError            = -18, // error when accessing the file
  kdsNullPointer            = -19, // a NULL pointer has been given as a parameter
  kdsReadOnWrite            = -20,
  kdsUnknownFileFlags       = -21, // an argument of type DSFILEFLAGS is invalid
  kdsBadSize                = -22,
  kdsRecordAlreadyInList    = -23, // a record is already in the list, cannot be replaced
  kdsRecordNotInList        = -24, // can't find the record in the file
  kdsUnknownRecordID        = -25, // the record ID (IDSURF2_...) is unknown
  kdsUnknownFileFormat      = -26, // the file format is unknown
  kdsBadObjectCount         = -27, // the number of objects in the file is invalid
  kdsInvalidStudiableSize   = -28, // size in points is invalid
  kdsInvalidXStep           = -29, // invalid X step
  kdsInvalidYStep           = -30, // invalid Y step
  kdsInvalidZStep           = -31, // invalid Z step
  kdsEmptyComment           = -32, // dsWriteObjectComment should not be called when the size
                                             // of the comment in the header is set to 0
  kdsWrongAPIVersion        = -33, // the version of the API compiled and the version of the user
                                             // are too different
  kdsInvalidFileHandle      = -34, // invalid handle of type DSFILE.
  kdsInvalidParamProfileInfo= -35, // invalid parametric profile information
  kdsInvalidWCount          = -36, // nWCount seems invalid
  kdsTotalPointsCountOverflow= -37, // too many points in the studiable
                                    // dimensions (nXCount * nYCount * nWCount) seems to generate an overflow
  kdsCantChangeCompression  = -38, // cannot change/set the compression if data has already been written to disk
                                   // compression must be set when opening the file and before writing the first object
  kdsInvalidBooleanArg = -39,     // boolean parameter must be TRUE (1) or FALSE (0)
  kdsCompressionFailure = -40,
  kdsInvalidBitsPerPoint = -41,
  kdsInvalidGroupArray      = -42, // invalid group array (null pointer?)
  kdsInvalidSectionArray    = -43, // invalid section array (null pointer?)
};
typedef enum DSRESULT DSRESULT;


// measurement unit
enum TUNIT 
{
  kUnit_unknown   =  0,   // unknown unit
  kUnit_none      =  0,   // no unit (unknown)
  kUnit_inch      =  1,   // inch
  kUnit_mm        =  2,   // millimeter
  kUnit_mA        =  3,   // milliampere
  kUnit_V         =  4,   // volt
  kUnit_N         =  5,   // newton
  kUnit_deg       =  6,   // degree
  kUnit_rad       =  7,   // radian
  kUnit_degK      =  8,   // Kelvin degree
  kUnit_degC      =  9,   // Celsius degree
  kUnit_degF      = 10,   // Fahrenheit degree
  kUnit_PerCent   = 11,   // %
  kUnit_sec       = 12,   // second
  kUnit_Hz        = 13,   // Hertz
  kUnit_Digit     = 14,   // digit
  kUnit_Pa        = 15,   // pascals
  kUnit_kbT       = 16,   // kbT
  kUnit_eV        = 17    // electronvolt
};
typedef enum TUNIT TUNIT;


// Type des attributs pouvant être présents dans les commentaires
enum DSATTRIBUTETYPE
{
  kTAxisAttribute = 0,
  kSensitivityConst = 1,
  kSpringConst = 2,
  kSpectrumNames = 3,
  kMaterialSide = 4,
  kCoordinateSystem = 5,
  kAlignmentId = 6,
  kSubType = 7,
  kShortName = 8,
  kColor = 9
};
typedef enum DSATTRIBUTETYPE DSATTRIBUTETYPE;



struct TSurfObjectInfos
{
  unsigned long ulSize;           // size of the structure


  DSSTUDIABLE Type;               // studiable type

  char  strName[31];              // name of the studiable

  char  strOperatorName[31];      // name of the operator who
                                  // measured the studiable

  short nAcquisitionType;         // which kind of sensor has been used
                                  // for the measure

  short nTracking;                // 0: normal tracking
                                  // 1: extended tracking
  
  short nSpecialPoints;           // 0: normal
                                  // 1: non-measured points

  BOOL  bAbsolute;                // FALSE: relatives values
                                  // TRUE: absolutes values
  
  float fGaugeResolution;         // 0: resolution not set

  long  nZMin;                    // min (resampled) value
  long  nZMax;                    // max (resampled) value

  long  nXCount;                  // number of points by column
  long  nYCount;                  // number of points by row
  long  nWCount;                  // number of points by depth (for hyperpectral measurements)

  float fXStep;                   // step
  float fYStep;                   // step
  float fZStep;                   // step

  float fXOffset;                 // offset
  float fYOffset;                 // offset
  float fZOffset;                 // offset

  char  strXAxisName[17];         // name of the X axis
  char  strYAxisName[17];         // name of the Y axis
  char  strZAxisName[17];         // name of the Z axis

  TUNIT tXAxisUnit;               // X axis unit
  TUNIT tYAxisUnit;               // Y axis unit
  TUNIT tZAxisUnit;               // Z axis unit

  char  strXAxisUnknownUnit[17];  // if unknown X unit, unit is present in this field
  char  strYAxisUnknownUnit[17];  // if unknown Y unit, unit is present in this field
  char  strZAxisUnknownUnit[17];  // if unknown Z unit, unit is present in this field

  BOOL  bInverted;                // are the values inverted ?
  
  short nRectified;               // 


  short nSecond;                  // date-time of the measure
  short nMinute;
  short nHour;
  short nDay;
  short nMonth;
  short nYear;
  float fMeasureLength;           // length (in seconds) of the measure

  char  ClientInfo[128];          // client informations

  short nCommentSize;             // size in bytes of the comment

  // *** T Axis ******************
  // *** only used with series ***
  
  float fTStep;                   // step
  float fTOffset;                 // offset
  TUNIT tTAxisUnit;               // T axis unit
  char  strTAxisUnknownUnit[14];  // if unknown T unit, unit is present in this field
  char  strTAxisName[14];         // name of the T axis

  // *** T Axis ******************
};
typedef struct TSurfObjectInfos TSurfObjectInfos;


struct TForceVolumeInfosSizes
{
  long nSignalsCount;
  long nMeasurementsCount;
  long nPhasesCount;
};
typedef struct TForceVolumeInfosSizes TForceVolumeInfosSizes;


struct TForceVolumeAxis
{
  float fStep;                  // axis step
  float fOffset;                // axis offset
  char  strAxisName[17];        // name of the axis
  TUNIT tAxisUnit;              // axis unit
  char  strAxisUnknownUnit[17]; // if unknown unit, unit is present in this field
};

struct TForceVolumeInfos
{
  DSSTUDIABLE nType;             // studiable type

  char strName[31];              // name of the studiable
  char strOperatorName[31];      // name of the operator who

  short nSpecialPoints;          // 0: normal
                                 // 1: non-measured points

  long nXSize;                   // number of columns (for a force volume)
  long nYSize;                   // number of rows (for a force volume)
  long nTSize;                   // number of elements (for a series)
  long nPSize;                   // number of signals
  long nSignalPointsCount;       // number of points for all measures in a signal
  long nPhasesCount;             // number of phases for all measurements

  TForceVolumeAxis tXAxis;       // X axis
  TForceVolumeAxis tYAxis;       // Y axis
  TForceVolumeAxis tWAxis;       // W axis

  short nSecond;                 // date-time of the measure
  short nMinute;
  short nHour;
  short nDay;
  short nMonth;
  short nYear;

  char  ClientInfo[128];          // client informations

  short nCommentSize;
};
typedef struct TForceVolumeInfos TForceVolumeInfos;


enum DSSIGNALTYPE
{
  kNotInit          = -1,
  kSignalUnknown    = 0,
  kSignalDeflection = 1,
  kSignalDistance   = 2,
  kSignalSeparation = 3,
  kSignalForce      = 4,
  kSignalTime       = 5
};
typedef enum DSSIGNALTYPE DSSIGNALTYPE;


enum DSPHASETYPE
{
  kPhaseUnknown  = 0,
  kPhaseApproach = 1,
  kPhaseRetract  = 2,
  kPhaseDwell    = 3,
  kPhaseEngage   = 4,
  kPhasePreload  = 5,
  KPhaseRecovery = 6,
  kPhaseMain     = 7
};
typedef enum DSPHASETYPE DSPHASETYPE;


struct TForceVolumeSignalInfos
{
  char         strName[31];  // name of the axis
  char         strUnit[14];  // axis unit
  DSSIGNALTYPE nSignalType = kNotInit;  // signal type (distance, deflexion, time, etc)
};
typedef struct TForceVolumeSignalInfos TForceVolumeSignalInfos;


struct TForceVolumeMeasurementInfos
{
  long   nSize =-1;
  char   strName[31];

  double dSensitivity;
  double dSpringConstant;

  double dXPosition;
  double dYPosition;
};
typedef struct TForceVolumeMeasurementInfos TForceVolumeMeasurementInfos;


struct TForceVolumePhaseInfos
{
  short       nMeasurementIndex;
  DSPHASETYPE nType;
  long        nOffset;
  long        nSize;
};
typedef struct TForceVolumePhaseInfos TForceVolumePhaseInfos;


// Description of a group from a parametric profile
struct TParametricProfileGroup
{
  BOOL bClosed;                 // is the group closed ?
  BOOL bDisplayClosed;          // is the group display closed ?
  long nNumberOfSection;        // Number of section of the group
};
typedef struct TParametricProfileGroup TParametricProfileGroup;

// Description of a section from a parametric profile
struct TParametricProfileSection
{
  long nStartPointIndex;        // Index of the first point of of the section (in the global array of points that is stored at the end of the file)
  long nNumberOfPoints;         // Number of points of the section
};
typedef struct TParametricProfileSection TParametricProfileSection;


// Description of a 2D point with double coordinates (used in parametric profile)
struct T2DDoublePoint
{
  double x;
  double y;
};
typedef struct T2DDoublePoint T2DDoublePoint;


// Description of curves positions infos
struct TCurvesPositionsInfos
{
  long nVersion; // Structure version.
  long nCount;   // Curves count.
};
typedef struct TCurvesPositionsInfos TCurvesPositionsInfos;


// Description of a curve position
struct TCurvePosition
{
  long   nCurveId;
  char   strXUnit[14];
  char   strYUnit[14];
  double dXPosition;
  double dYPosition;
};
typedef struct TCurvePosition TCurvePosition;


// typedef function pointer for dsLoadAPI()
typedef DSRESULT (__stdcall *PFNDSLOADAPI)(unsigned long, struct TSurfAPI*);


// types defined
#define SIZE_OF_DSCHAR  1
typedef char        DSCHAR;
typedef DSCHAR*     DSSTRING;
typedef DSCHAR      DSSTRING16[16+1];


#define  SIZE_OF_DSUNICHAR  2
typedef wchar_t     DSUNICHAR;

const long kdsMinPointValue    = 0x80000001; // -2147483647
                                             // minimum legal value for a point

const long kdsMaxPointValue    = 0x7FFFFFFF; //  2147483647
                                             // maximum legal value for a point

const long kdsNonMeasuredPoint = 0x80000000; // -2147483648
                                             // value for a non measured point




// structure which contains all the functions of the API
// (used to ease the link between client & dll)
struct TSurfAPI
{
  // Structure size in bytes
  unsigned long ulSize;

  // *** API functions for version 1 ***
  struct
  {
    // ANSI version
    DSRESULT (__stdcall *dsOpenStudiable)  (const char*    strFilename, DSFILEFLAGS rw, DSSTUDIABLE* pType, unsigned short* pCount, DSFILE* pFileHandle);
    // UNICODE version
    DSRESULT (__stdcall *dsOpenStudiableW) (const wchar_t* strFilename, DSFILEFLAGS rw, DSSTUDIABLE* pType, unsigned short* pCount, DSFILE* pFileHandle);
    
    DSRESULT (__stdcall *dsCloseStudiable)(DSFILE file);
    DSRESULT (__stdcall *dsAbortOpsOnStudiable)(DSFILE file);


    DSRESULT (__stdcall *dsReadObjectInfos) (DSFILE file, long nObject, struct TSurfObjectInfos* pInfos);
    DSRESULT (__stdcall *dsWriteObjectInfos)(DSFILE file, long nObject, struct TSurfObjectInfos* pInfos);

    DSRESULT (__stdcall *dsReadObjectComment) (DSFILE file, long nObject, char* strComment);
    DSRESULT (__stdcall *dsWriteObjectComment)(DSFILE file, long nObject, const char* strComment);

    DSRESULT (__stdcall *dsReadParametricProfileInformation) (DSFILE file,
                                                              long nGroupNb,
                                                              struct TParametricProfileGroup* parametricProfileGroupArray,
                                                              long nSectionsNb,
                                                              struct TParametricProfileSection *pParametricProfileSectionArray,
                                                              BOOL *pMaterialAtRight,
                                                              long *pTotalPointsNb);
    DSRESULT (__stdcall *dsWriteParametricProfileInformation)(DSFILE file,
                                                              long nGroupNb,
                                                              struct TParametricProfileGroup* parametricProfileGroupArray,
                                                              long nSectionsNb,
                                                              struct TParametricProfileSection *pParametricProfileSectionArray,
                                                              BOOL bMaterialAtRight);

    DSRESULT (__stdcall *dsReadObjectPoints) (DSFILE file, long nObject, long* pBuffer);
    DSRESULT (__stdcall *dsWriteObjectPoints)(DSFILE file, long nObject, const long* pBuffer);
  
    DSRESULT (__stdcall *dsReadParametricProfilePoints) (DSFILE file, T2DDoublePoint* pBuffer);
    DSRESULT (__stdcall *dsWriteParametricProfilePoints)(DSFILE file, const T2DDoublePoint* pBuffer);

    DSRESULT (__stdcall *dsReadForceVolumeConstants) (DSFILE file, long nObject, double* pBuffer);
    DSRESULT (__stdcall *dsWriteForceVolumeConstants)(DSFILE file, long nObject, const double* pBuffer);

    DSRESULT(__stdcall *dsGetCompression) (DSFILE file, BOOL* pEnableCompression);
    DSRESULT(__stdcall *dsSetCompression) (DSFILE file, BOOL bEnableCompression);

    DSRESULT(__stdcall *dsReadParametricProfileMaterialSides) (DSFILE file, long nGroupNb, long* pBuffer);
    DSRESULT(__stdcall *dsWriteParametricProfileMaterialSides)(DSFILE file, const long* pBuffer);

    DSRESULT(__stdcall *dsReadForceVolumeInfos)(DSFILE file, struct TForceVolumeInfos* pSizes);
    DSRESULT(__stdcall *dsReadForceVolumeSignalInfos)(DSFILE file, struct TForceVolumeSignalInfos* pBuffer);
    DSRESULT(__stdcall *dsReadForceVolumeMeasurementInfos)(DSFILE file, struct TForceVolumeMeasurementInfos* pBuffer);
    DSRESULT(__stdcall *dsReadForceVolumePhaseInfos)(DSFILE file, struct TForceVolumePhaseInfos* pBuffer);
    DSRESULT(__stdcall *dsReadForceVolumePoints)(DSFILE file, double* pBuffer);

    DSRESULT(__stdcall *dsWriteForceVolumeInfos)(DSFILE file, const struct TForceVolumeInfos* pSizes);
    DSRESULT(__stdcall *dsWriteForceVolumeSignalInfos)(DSFILE file, const struct TForceVolumeSignalInfos* pBuffer);
    DSRESULT(__stdcall *dsWriteForceVolumeMeasurementInfos)(DSFILE file, const struct TForceVolumeMeasurementInfos* pBuffer);
    DSRESULT(__stdcall *dsWriteForceVolumePhaseInfos)(DSFILE file, const struct TForceVolumePhaseInfos* pBuffer);
    DSRESULT(__stdcall *dsWriteForceVolumePoints)(DSFILE file, const double* pBuffer);

    DSRESULT(__stdcall *dsReadCurvesPositionsInfos) (DSFILE file, long nObject,       struct TCurvesPositionsInfos& infos);
    DSRESULT(__stdcall *dsWriteCurvesPositionsInfos)(DSFILE file, long nObject, const struct TCurvesPositionsInfos& infos);
    DSRESULT(__stdcall *dsReadCurvesPositions)      (DSFILE file, long nObject,       struct TCurvePosition* pPositons);
    DSRESULT(__stdcall *dsWriteCurvesPositions)     (DSFILE file, long nObject, const struct TCurvePosition* pPositons);
  } Version_1;

 
  // *** helper functions ***
  struct
  { 
    DSFORMAT (__stdcall *dsGetFileFormat)(const char* strFilename);

    DSFORMAT (__stdcall *dsGetFileFormatW)(const wchar_t* strFilename);
    
    DSRESULT (__stdcall *dsSaveStudiable)(const char* strFilename,
                                DSFORMAT Format,
                                DSSTUDIABLE Type,
                                long nXCount, TUNIT tXunit, float fXStep, float fXOffset,
                                long nYCount, TUNIT tYUnit, float fYStep, float fYOffset,
                                TUNIT tZUnit, float fZStep, float fZOffset,
                                const long* pBuffer,
                                BOOL bNonMeasuredPoints);

    DSRESULT (__stdcall *dsSaveStudiableW)(const wchar_t* strFilename,
                                DSFORMAT Format,
                                DSSTUDIABLE Type,
                                long nXCount, TUNIT tXunit, float fXStep, float fXOffset,
                                long nYCount, TUNIT tYUnit, float fYStep, float fYOffset,
                                TUNIT tZUnit, float fZStep, float fZOffset,
                                const long* pBuffer,
                                BOOL bNonMeasuredPoints);

    DSRESULT (__stdcall *dsLoadAPI)(unsigned long ulAPIversion, struct TSurfAPI* pSurfAPI);

    DSRESULT (__stdcall *dsReadObjectInfosWithoutStruct)(DSFILE file, long nObject,
                                DSSTUDIABLE* Type,
                                char* strName, char* strOperatorName,
                                short* nAcquisitionType, 
                                short* nTracking, short* nSpecialPoints,
                                BOOL* bAbsolute, float* fGaugeResolution,
                                long* nZMin, long* nZMax,
                                long* nXCount, long* nYCount,
                                float* fXStep, float* fYStep, float* fZStep,
                                float* fXOffset, float* fYOffset, float* fZOffset,
                                char* strXAxisName, char* strYAxisName, char* strZAxisName,
                                TUNIT* tXAxisUnit, TUNIT* tYAxisUnit, TUNIT* tZAxisUnit,
                                BOOL*  bInverted,
                                short* nRectified,
                                short* nSecond, short* nMinute, short* nHour, short* nDay, short* nMonth, short* nYear,
                                float* fMeasureLength,
                                char* ClientInfo,
                                short* nCommentSize);
  
  DSRESULT (__stdcall *dsWriteObjectInfosWithoutStruct)(DSFILE file, long nObject, 
                                DSSTUDIABLE Type,
                                char* strName, char* strOperatorName,
                                short nAcquisitionType, 
                                short nTracking, short nSpecialPoints,
                                BOOL bAbsolute, float fGaugeResolution,
                                long nZMin, long nZMax,
                                long nXCount, long nYCount,
                                float fXStep, float fYStep, float fZStep,
                                float fXOffset, float fYOffset, float fZOffset,
                                char* strXAxisName, char* strYAxisName, char* strZAxisName,
                                TUNIT tXAxisUnit, TUNIT tYAxisUnit, TUNIT tZAxisUnit,
                                BOOL  bInverted,
                                short nRectified,
                                short nSecond, short nMinute, short nHour, short nDay, short nMonth, short nYear,
                                float fMeasureLength,
                                char* ClientInfo,
                                short nCommentSize);
  } Helper;

};
typedef struct TSurfAPI TSurfAPI;


#pragma pack( pop, SurfPack )

#ifdef __cplusplus
}
#endif

#endif // _SurfAPI_h
using Microsoft.SqlServer.Server;
using System;
using System.Runtime.InteropServices;
using System.Runtime.Remoting;
using System.Text;

namespace SurfApiTest
{
    enum DSSTUDIABLE
    {
        kdsUnknown = -1,

        kdsFirstStudiable = 1,

        kdsProfile = 1,
        kdsSurface = 2,
        kdsBinaryImage = 3,
        kdsProfileSeries = 4,
        kdsSurfaceSeries = 5,
        kdsMeridianDisc = 6,
        kdsMultiLayerProfile = 7,
        kdsMultiLayerSurface = 8,

        kdsParallelDisc = 9,  // not yet implemented

        kdsIntensityImage = 10,
        kdsIntensitySurface = 11,

        kdsRGBImage = 12,
        kdsRGBSurface = 13,

        kdsForceCurve = 14,
        kdsSeriesOfForceCurve = 15,

        kdsRGBIntensitySurface = 16,

        kdsParametricProfile = 17,

        kdsRGBImagesSeries = 18,

        kdsParametricSurface = 19, // not yet implemented

        kdsSpectrum = 20,

        kdsHyperSpectral = 21,

        kdsRoundnessProfile = 22,
        kdsMultiRoundnessProfile = 23,
        kdsFlatnessProfile = 24,
        kdsMultiFlatnessProfile = 25,

        kdsForceVolume = 26,
        kdsForceVolumeSpringConst = 27,
        kdsForceVolumeSensitivityConst = 28,

        kdsCITSSpectrum = 29,
        kdsCITSCube = 30,

        kdsMultiHorizontalStraightnessProfile = 31, // not yet implemented
        kdsMultiVerticalStraightnessProfile = 32, // not yet implemented
        kdsHelicoidalRoundnessProfile = 33, // not yet implemented
        kdsSpiralFlatnessProfile = 34, // not yet implemented

        kdsParametricForceCurve = 35,
        kdsSeriesOfParametricForceCurve = 36,
        kdsParametricForceVolume = 37,

        kdsCloudParametricSurface = 38, // not yet implemented
        kdsMultiChannelImage = 39,
        kdsMultiChannelVolume = 40, // not yet implemented

        kdsLastStudiable = kdsMultiChannelVolume
    }
    enum DSRESULT
    {
        kdsOK = 1, // success !
        kdsError = 0, // generic error
        kdsInvalidFilename = -1, // invalid filename
        kdsInvalidObject = -2, // invalid object number
        kdsInvalidInfos = -3, // structure infos
        kdsInvalidComment = -4, // invalid comment
        kdsInvalidPoints = -5, // invalid array of points
        kdsAlreadyOpen = -6, // file already open
        kdsNotEnoughMemory = -7, // not enough memory to run the operation
        kdsNotImplemented = -8, // function not yet implemented
        kdsInvalidPointSize = -9, // the size of the points is incorrect
        kdsInvalid1stArg = -10, //
        kdsInvalid2ndArg = -11, //
        kdsInvalid3rdArg = -12, //
        kdsInvalid4thArg = -13, //
        kdsUnknownStudiable = -14, // invalid studiable type
        kdsWriteOnRead = -15, // can't write in a file when open for reading
        kdsWrongObjectIndex = -16, // the index of the object is not in the authorised range
        kdsWrongWriteOperation = -17, // error in the order of the writing operations
        kdsIOFileError = -18, // error when accessing the file
        kdsNullPointer = -19, // a NULL pointer has been given as a parameter
        kdsReadOnWrite = -20,
        kdsUnknownFileFlags = -21, // an argument of type DSFILEFLAGS is invalid
        kdsBadSize = -22,
        kdsRecordAlreadyInList = -23, // a record is already in the list, cannot be replaced
        kdsRecordNotInList = -24, // can't find the record in the file
        kdsUnknownRecordID = -25, // the record ID (IDSURF2_...) is unknown
        kdsUnknownFileFormat = -26, // the file format is unknown
        kdsBadObjectCount = -27, // the number of objects in the file is invalid
        kdsInvalidStudiableSize = -28, // size in points is invalid
        kdsInvalidXStep = -29, // invalid X step
        kdsInvalidYStep = -30, // invalid Y step
        kdsInvalidZStep = -31, // invalid Z step
        kdsEmptyComment = -32, // dsWriteObjectComment should not be called when the size
                               // of the comment in the header is set to 0
        kdsWrongAPIVersion = -33, // the version of the API compiled and the version of the user
                                  // are too different
        kdsInvalidFileHandle = -34, // invalid handle of type DSFILE.
        kdsInvalidParamProfileInfo = -35, // invalid parametric profile information
        kdsInvalidWCount = -36, // nWCount seems invalid
        kdsTotalPointsCountOverflow = -37, // too many points in the studiable
                                           // dimensions (nXCount * nYCount * nWCount) seems to generate an overflow
        kdsCantChangeCompression = -38, // cannot change/set the compression if data has already been written to disk
                                        // compression must be set when opening the file and before writing the first object
        kdsInvalidBooleanArg = -39,     // boolean parameter must be TRUE (1) or FALSE (0)
        kdsCompressionFailure = -40,
        kdsInvalidBitsPerPoint = -41,
        kdsInvalidGroupArray = -42, // invalid group array (null pointer?)
        kdsInvalidSectionArray = -43, // invalid section array (null pointer?)
    }
    enum DSFILEFLAGS
    {
        kdsNoFile = 0, // used for internal purpose

        kdsReadFile = 1,
        kdsWriteFile = 2
    }
    enum TUNIT
    {
        kUnit_unknown = 0,   // unknown unit
        kUnit_none = 0,   // no unit (unknown)
        kUnit_inch = 1,   // inch
        kUnit_mm = 2,   // millimeter
        kUnit_mA = 3,   // milliampere
        kUnit_V = 4,   // volt
        kUnit_N = 5,   // newton
        kUnit_deg = 6,   // degree
        kUnit_rad = 7,   // radian
        kUnit_degK = 8,   // Kelvin degree
        kUnit_degC = 9,   // Celsius degree
        kUnit_degF = 10,   // Fahrenheit degree
        kUnit_PerCent = 11,   // %
        kUnit_sec = 12,   // second
        kUnit_Hz = 13,   // Hertz
        kUnit_Digit = 14,   // digit
        kUnit_Pa = 15,   // pascals
        kUnit_kbT = 16,   // kbT
        kUnit_eV = 17    // electronvolt
    }
    enum DSFORMAT
    {
        kFormatUnknown = 0, // unknown format
        kFormatSurf1 = 1, // format Surf 1
        kFormatSurf2 = 2, // format Surf 2
        kFormatSDF = 3, // format SDF

        kFormatCompressedSurf1 = 4, // format Surf 1, data compressed using zlib
    }

    struct TSurfObjectInfos
    {
        ulong ulSize;           // size of the structure


        public DSSTUDIABLE nType;               // studiable type

        public byte[] strName;              // name of the studiable

        public byte[] strOperatorName;      // name of the operator who
                                       // measured the studiable

        public int nAcquisitionType;         // which kind of sensor has been used
                                        // for the measure

        public short nTracking;                // 0: normal tracking
                                        // 1: extended tracking

        public short nSpecialPoints;           // 0: normal
                                        // 1: non-measured points

        public bool bAbsolute;                // FALSE: relatives values
                                       // TRUE: absolutes values

        public float fGaugeResolution;         // 0: resolution not set

        public long nZMin;                    // min (resampled) value
        public long nZMax;                    // max (resampled) value

        public long nXCount;                  // number of points by column
        public long nYCount;                  // number of points by row
        public long nWCount;                  // number of points by depth (for hyperpectral measurements)

        public float fXStep;                   // step
        public float fYStep;                   // step
        public float fZStep;                   // step

        public float fXOffset;                 // offset
        public float fYOffset;                 // offset
        public float fZOffset;                 // offset

        public byte[] strXAxisName;         // name of the X axis
        public byte[] strYAxisName;         // name of the Y axis
        public byte[] strZAxisName;         // name of the Z axis

        public TUNIT tXAxisUnit;               // X axis unit
        public TUNIT tYAxisUnit;               // Y axis unit
        public TUNIT tZAxisUnit;               // Z axis unit

        public byte[] strXAxisUnknownUnit;  // if unknown X unit, unit is present in this field
        public byte[] strYAxisUnknownUnit;  // if unknown Y unit, unit is present in this field
        public byte[] strZAxisUnknownUnit;  // if unknown Z unit, unit is present in this field

        public bool bInverted;                // are the values inverted ?

        public short nRectified;               //


        public short nSecond;                  // date-time of the measure
        public short nMinute;
        public short nHour;
        public short nDay;
        public short nMonth;
        public short nYear;
        public float fMeasureLength;           // length (in seconds) of the measure

        public byte[] ClientInfo;          // client informations

        public short nCommentSize;             // size in bytes of the comment

        // *** T Axis ******************
        // *** only used with series ***

        float fTStep;                   // step
        float fTOffset;                 // offset
        TUNIT tTAxisUnit;               // T axis unit
        public byte[] strTAxisUnknownUnit;  // if unknown T unit, unit is present in this field
        public byte[] strTAxisName;         // name of the T axis

        // *** T Axis ******************
    }

    class SurfApi
    {
        [DllImport("surfapi.dll")]
        private static extern DSRESULT dsOpenStudiable(ref byte StrFileName, DSFILEFLAGS rw, ref DSSTUDIABLE pType, ref int pCount, ref long pFileHandle);
        [DllImport("surfapi.dll")]
        private static extern DSRESULT dsCloseStudiable(long file);
        [DllImport("surfapi.dll")]
        private static extern DSRESULT dsAbortOpsOnStudiable(long file);
        [DllImport("surfapi.dll")]
        private static extern DSRESULT dsReadObjectInfos(long file, long nObject, ref TSurfObjectInfos pInfos);
        [DllImport("surfapi.dll")]
        private static extern DSRESULT dsWriteObjectInfos(long file, long nObject, ref TSurfObjectInfos pInfos);
        [DllImport("surfapi.dll")]
        private static extern DSRESULT dsReadObjectComment(long file, long nObject, ref string strComment);
        [DllImport("surfapi.dll")]
        private static extern DSRESULT dsWriteObjectComment(long file, long nObject, string strComment);
        [DllImport("surfapi.dll")]
        private static extern DSRESULT dsReadObjectPoints(long file, long nObject, ref long pBuffer);
        [DllImport("surfapi.dll")]
        private static extern DSRESULT dsWriteObjectPoints(long file, long nObject, long pBuffer);
        [DllImport("surfapi.dll")]
        private static extern DSRESULT dsReadObjectInfosWithoutStruct(long file, long nObject, ref DSSTUDIABLE pType, ref byte strName, ref byte strOperatorName, ref int nAcquisitionType, ref int nTracking, ref int nSpecialPoints, ref byte bAbsolute, ref float fGaugeResolution, ref long nZMin, ref long nZMax, ref long nXCount, ref long nYCount, ref float fXStep, ref float fYStep, ref float fZStep, ref float fXOffset, ref float fYOffset, ref float fZOffset, ref byte strXAxisName, ref byte strYAxisName, ref byte strZAxisName, ref TUNIT tXAxisUnit, ref TUNIT tYAxisUnit, ref TUNIT tZAxisUnit, ref byte bInverted, ref int nRectified, ref int nSecond, ref int nMinute, ref int nHour, ref int nDay, ref int nMonth, ref int nYear, ref float fMeasureLength, ref byte ClientInfo, ref int nCommentSize);
        [DllImport("surfapi.dll")]
        private static extern DSRESULT dsWriteObjectInfosWithoutStruct(long file, long nObject, DSSTUDIABLE pType, ref byte strName, ref byte strOperatorName, int nAcquisitionType, int nTracking, int nSpecialPoints, byte[] bAbsolute, Single fGaugeResolution, long nZMin, long nZMax, long nXCount, long nYCount, Single fXStep, Single fYStep, Single fZStep, Single fXOffset, Single fYOffset, Single fZOffset, ref byte[] strXAxisName, ref byte[] strYAxisName, ref byte[] strZAxisName, TUNIT tXAxisUnit, TUNIT tYAxisUnit, TUNIT tZAxisUnit, byte[] bInverted, int nRectified, int nSecond, int nMinute, int nHour, int nDay, int nMonth, int nYear, Single fMeasureLength, ref byte[] ClientInfo, int nCommentSize);
        [DllImport("surfapi.dll")]
        private static extern DSRESULT dsSaveStudiable(byte strFileName, DSFORMAT Format, DSSTUDIABLE pType, long nXCount, TUNIT tXunit, float fXStep, float fXOffset, long nYCount, TUNIT tYunit, float fYStep, float fYOffset, TUNIT tZUnit, float fZStep, float fZOffset, long pBuffer, byte bNonMeasuredPoints);

        public SurfApi()
        {
            TSurfObjectInfos tSurfObjectInfos;

            tSurfObjectInfos.strName = new byte[31];
            tSurfObjectInfos.strOperatorName = new byte[31];

            tSurfObjectInfos.strXAxisName = new byte[17];
            tSurfObjectInfos.strYAxisName = new byte[17];
            tSurfObjectInfos.strZAxisName = new byte[17];

            tSurfObjectInfos.strXAxisUnknownUnit = new byte[17];
            tSurfObjectInfos.strYAxisUnknownUnit = new byte[17];
            tSurfObjectInfos.strZAxisUnknownUnit = new byte[17];

            tSurfObjectInfos.ClientInfo = new byte[128];

            tSurfObjectInfos.strTAxisUnknownUnit = new byte[14];
            tSurfObjectInfos.strTAxisName = new byte[14];
        }

        private bool DisplaySurf(string strSurfFile, string strFileNameOut)
        {
            bool result = false;
            DSSTUDIABLE nStudiableType = DSSTUDIABLE.kdsSurface;
            int nObjectCount = 3;
            DSRESULT nResult; // return code
            long hFile; // file handle
            hFile = 0L;
            byte[] byteFileName = Encoding.ASCII.GetBytes(strSurfFile);

            // We try to open the file
            nResult = dsOpenStudiable(ref byteFileName[0], DSFILEFLAGS.kdsReadFile, ref nStudiableType, ref nObjectCount, ref hFile);

            // Verify the success of the operation
            if (DSRESULT.kdsOK != nResult)
            {
                result = false;
                return result;
            }
            long i;
            for (i = 1L; i <= nObjectCount; i++)
            {

                // Initialise the object header
                TSurfObjectInfos Infos;
                //nResult = dsReadObjectInfosWithoutStruct(hFile, i, ref Infos.nType, ref Infos.strName[0], ref Infos.strOperatorName[0], ref Infos.nAcquisitionType, Infos.nTracking, Infos.nSpecialPoints, Infos.bAbsolute, Infos.fGaugeResolution, Infos.nZMin, Infos.nZMax, Infos.nXCount, Infos.nYCount, Infos.fXStep, Infos.fYStep, Infos.fZStep, Infos.fXOffset, Infos.fYOffset, Infos.fZOffset, Infos.strXAxisName[0], Infos.strYAxisName[0], Infos.strZAxisName[0], Infos.tXAxisUnit, Infos.tYAxisUnit, Infos.tZAxisUnit, Infos.bInverted, Infos.nRectified, Infos.nSecond, Infos.nMinute, Infos.nHour, Infos.nDay, Infos.nMonth, Infos.nYear, Infos.fMeasureLength, Infos.ClientInfo[0], Infos.nCommentSize);
                // Reading the information concerning the object


                // Verify the success of the operation
                if (DSRESULT.kdsOK != nResult)
                {
                    // close the file
                    nResult = dsAbortOpsOnStudiable(hFile);
                    return false;
                }

                // The information has been read successfully
                // We can work on it
                // PLACE YOUR PROCESS HERE
                // ...

            }

            result = (DSRESULT.kdsOK == dsCloseStudiable(hFile));
            return result;
        }

        public bool SaveSurface(string strFileNameOut)
        {
            bool result;
            int nObjectCount = 1;
            DSRESULT nResult = DSRESULT.kdsOK; // return code
            long hFile; // file handle
            hFile = 0L;

            // Verify the success of the operation
            if (DSRESULT.kdsOK != nResult)
            {
                result = false;
                return result;
            }
            long i;
            for (i = 1L; i <= nObjectCount; i++)
            {
                TSurfObjectInfos Infos;
                Infos.nXCount = 10;
                Infos.tXAxisUnit = TUNIT.kUnit_mm;
                Infos.fXStep = 0;
                Infos.fXOffset = 0;

                Infos.nYCount = 10;
                Infos.tYAxisUnit = TUNIT.kUnit_mm;
                Infos.fYStep = 0;
                Infos.fYOffset = 0;

                Infos.tZAxisUnit = TUNIT.kUnit_mm;
                Infos.fZStep = 0;
                Infos.fZOffset = 0;

                long[] pBuffer;
                pBuffer = new long[(Infos.nXCount * Infos.nYCount)];

                // output buffer
                long[] pBufferOut;
                pBufferOut = new long[(Infos.nXCount * Infos.nYCount)];

                // Read the points
                nResult = dsReadObjectPoints(hFile, i, ref pBuffer[0]);

                // output file
                byte[] byteFileNameOut = Encoding.ASCII.GetBytes(strFileNameOut);

                // Save data to disk
                nResult = dsSaveStudiable(byteFileNameOut[0], DSFORMAT.kFormatSurf1, DSSTUDIABLE.kdsSurface, Infos.nXCount, Infos.tXAxisUnit, Infos.fXStep, Infos.fXOffset, Infos.nYCount, Infos.tYAxisUnit, Infos.fYStep, Infos.fYOffset, Infos.tZAxisUnit, Infos.fZStep, Infos.fZOffset, pBufferOut[0], 0);
            }
            result = (DSRESULT.kdsOK == nResult);
            return result;
        }
    }
}

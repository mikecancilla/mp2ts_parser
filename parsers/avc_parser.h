#include <base_parser.h>

class BitStream;

enum eAVCNaluType
{
    eAVCNaluType_Unspecified = 0,
    eAVCNaluType_CodedSliceNonIdrPicture = 1,
    eAVCNaluType_CodedSliceDataPartitionA = 2,
    eAVCNaluType_CodedSliceDataPartitionB = 3,
    eAVCNaluType_CodedSliceDataPartitionC = 4,
    eAVCNaluType_CodedSliceIdrPicture = 5,
    eAVCNaluType_SupplementalEnhancementInformation = 6,
    eAVCNaluType_SequenceParameterSet = 7,
    eAVCNaluType_PictureParameterSet = 8,
    eAVCNaluType_AccessUnitDelimiter = 9,
    eAVCNaluType_EndOfSequence = 10,
    eAVCNaluType_EndOfStream = 11,
    eAVCNaluType_FillerData = 12,
    eAVCNaluType_SequenceParameterSetExtension = 13,
    eAVCNaluType_PrefixNalUnit = 14,
    eAVCNaluType_SubsetSequenceParameterSet = 15,
    eAVCNaluType_ReservedStart1 = 16,
    eAVCNaluType_ReservedEnd1 = 18,
    eAVCNaluType_CodedSliceAuxiliaryPicture = 19,
    eAVCNaluType_CodedSliceExtension = 20,
    eAVCNaluType_ReservedStart2 = 21,
    eAVCNaluType_ReservedEnd2 = 23,
    eAVCNaluType_UnspecifiedStart = 24,
    eAVCNaluType_UnspecifiedEnd = 25
};

// https://blog.pearce.org.nz/2013/11/what-does-h264avc1-codecs-parameters.html
enum eAVCProfile {
  eAVCProfile_unknown                    = 0, 
  eAVCProfile_Simple                     = 66, 
  eAVCProfile_Base                       = 66, 
  eAVCProfile_Main                       = 77, 
  eAVCProfile_High                       = 100, 
  eAVCProfile_422                        = 122, 
  eAVCProfile_High10                     = 110, 
  eAVCProfile_444                        = 144, 
  eAVCProfile_Extended                   = 88, 
  eAVCProfile_ScalableBase               = 83, 
  eAVCProfile_ScalableHigh               = 86, 
  eAVCProfile_MultiviewHigh              = 118, 
  eAVCProfile_StereoHigh                 = 128, 
  eAVCProfile_ConstrainedBase            = 256, 
  eAVCProfile_UCConstrainedHigh          = 257, 
  eAVCProfile_UCScalableConstrainedBase  = 258, 
  eAVCProfile_UCScalableConstrainedHigh  = 259 
};

// https://blog.pearce.org.nz/2013/11/what-does-h264avc1-codecs-parameters.html
enum eAVCLevel {
  eAVCLevel1    = 10, 
  eAVCLevel1_b  = 11, 
  eAVCLevel1_1  = 11, 
  eAVCLevel1_2  = 12, 
  eAVCLevel1_3  = 13, 
  eAVCLevel2    = 20, 
  eAVCLevel2_1  = 21, 
  eAVCLevel2_2  = 22, 
  eAVCLevel3    = 30, 
  eAVCLevel3_1  = 31, 
  eAVCLevel3_2  = 32, 
  eAVCLevel4    = 40, 
  eAVCLevel4_1  = 41, 
  eAVCLevel4_2  = 42, 
  eAVCLevel5    = 50, 
  eAVCLevel5_1  = 51, 
  eAVCLevel5_2  = 51
};

class avc_parser : public base_parser
{
public:
    // Process frames_wanted frames at a time
    virtual size_t process_video_frames(uint8_t *p, size_t PES_packet_data_length, unsigned int frames_wanted, unsigned int &frames_received, bool b_xml_out = false) override;

private:
    // Entire available stream in memory
    size_t process_sequence_parameter_set(uint8_t *&p);
    size_t process_vui_parameters(BitStream &bs);
    size_t process_picture_parameter_set(uint8_t *&p);
    size_t process_slice_layer_without_partitioning(uint8_t *&p);
    size_t process_slice_header(uint8_t *&p);
    size_t process_access_unit_delimiter(uint8_t *&p);
    size_t process_sei_message(uint8_t *&p, uint8_t *pLastByte);
    size_t process_recovery_point_sei(uint8_t *&p);

    uint8_t EGParse(BitStream &bs, uint32_t &bitsRead);
};
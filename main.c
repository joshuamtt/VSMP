#include <asm-generic/errno-base.h>
#include <libavcodec/codec.h>
#include <libavcodec/codec_par.h>
#include <libavutil/avutil.h>
#include <libavutil/error.h>
#include <libavutil/frame.h>
#include <libavutil/log.h>
#include <libavutil/pixfmt.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"
#include "config.h"
#include "dither.h"
#include <sys/queue.h>

// Functions
int find_codec_parameters(AVCodecParameters** p_CodecParams, AVFormatContext* p_avformat_ctx);
void dither_buffer(uint8_t** buff, enum Dither_op dither, int width, int height);

#define WIDTH 640
#define HEIGHT 480

int main(int argc, char *argv[]) {

  // TODO: add options into command line args...
  // for ex. VSMP --help
  // VSMP FILENAME DITHER_OP

  if (argc < 3) {
    printf("Usage: VSMP <file> <dither choice>");
    return -1;
  }


  enum Dither_op user_dither = atoi(argv[2]); // TODO: atoi sucks! change into something else.

  // FFMPEG
  AVCodecParameters *p_CodecParams = NULL;
  int video_stream_index;
  char* file_name = argv[1];
  AVFormatContext *p_avformat_ctx = avformat_alloc_context();
  
  if (avformat_open_input(&p_avformat_ctx, file_name, NULL, NULL) != 0) {
    printf("Failure opening input");
    return -1;
  }
  video_stream_index = find_codec_parameters(&p_CodecParams, p_avformat_ctx);
  if (video_stream_index == -1) {
    printf("Error finding streams\n");
    return -1;
  }
  const AVCodec* p_Codec = avcodec_find_decoder(p_CodecParams->codec_id);

  if (!p_Codec) {
    printf("Error finding decoder.\n");
    return -1;
  }
  // Allocate an AVCodecContext
  AVCodecContext *p_codecCTX = avcodec_alloc_context3(p_Codec);
  if (!p_codecCTX) {
    printf("Failed allocating memory for AVCodecContext");
    return -1;
  }
  // Copy codec params over.
  if (avcodec_parameters_to_context(p_codecCTX, p_CodecParams) < 0) {
    printf("Failed to copy codec params to codec context");
    return -1;
  }
 
  if (avcodec_open2(p_codecCTX, p_Codec, NULL) < 0) {
    printf("Failed to open codec through avcodec_open2");
    return -1;
  }

  
  // Decode function that accepts the packet, codec context, and frame.
  AVFrame *p_Frame = av_frame_alloc();
  if (!p_Frame) {
    printf("Failed to allocate memory for AVFrame.");
    return -1;
  }
  AVPacket *p_Packet = av_packet_alloc();
  if (!p_Packet) {
    printf("Failed to allocate memory for AVPacket");
    return -1;
  }
  // int response = 0;
  // int packets_to_process = 1;

  
  int running = 1;
  int frame_response;

  struct SwsContext* sws_context = sws_alloc_context();

  sws_context = sws_getContext(p_CodecParams->width, 
                             p_CodecParams->height, 
                             AV_PIX_FMT_YUV420P, 
                             WIDTH, 
                             HEIGHT, 
                             AV_PIX_FMT_RGB24,
                             SWS_BICUBIC, 
                             NULL, 
                             NULL, 
                             NULL);

  if (!sws_context) {
    printf("Invalid SWS_CONTEXT\n");
    return -1;
  }

// Main Loop
  while (running) {

    if (av_read_frame(p_avformat_ctx, p_Packet)>=0) {
    // Successfully sent a packet.
      if (p_Packet->stream_index==video_stream_index) {

        if (avcodec_send_packet(p_codecCTX, p_Packet)>=0) {

          frame_response = avcodec_receive_frame(p_codecCTX, p_Frame);

          if (frame_response==AVERROR(EAGAIN) || frame_response == AVERROR_EOF) {
            break;
          } else if (frame_response < 0) {
            av_log(NULL, AV_LOG_ERROR, "ERROR\n");
            return -1;
          }

          if (frame_response >=0) { // We got a frame.
            // Two things are needed to be done with this frame. 
            // 1. Convert from YUV to RGB. 
            // convertframe_YUV_RGB();
            // 2. Copy the pixel data from the RGB Frame to a buffer.
            //
            // Will have to put the buffer to the EINK screen.
            

            AVFrame* destination_frame = av_frame_alloc(); 
            destination_frame->format = AV_PIX_FMT_RGB24;
            destination_frame->width = WIDTH;
            destination_frame->height = HEIGHT;
            av_frame_get_buffer(destination_frame, 24);

            int ret;

            ret = av_image_fill_linesizes(destination_frame->linesize,
                                          AV_PIX_FMT_RGB24,
                                          destination_frame->width);

            if (ret < 0) {
              printf("Error filling linesizes.\n");
              return -1;
            }
            // scale from YUV -> RGB24
            ret = sws_scale_frame(sws_context, destination_frame, p_Frame);
            if (ret < 0) {
              printf("error scaling frame\n");
              return -1;
            }

            int rgb_buff_size = av_image_get_buffer_size(AV_PIX_FMT_RGB24,
                                                         destination_frame->width, 
                                                         destination_frame->height, 
                                                         32);

            uint8_t* rgb_buff; // buffer that will be dithered, and then uploaded.

            rgb_buff = malloc(rgb_buff_size);

            if (!rgb_buff) {
              printf("Error allocating rgb buff.\n");
              return -1;
            }
            ret = av_image_copy_to_buffer(rgb_buff,
                                          rgb_buff_size, 
                                          (const unsigned char* const*)destination_frame->data, 
                                          destination_frame->linesize, 
                                          AV_PIX_FMT_RGB24,
                                          WIDTH, HEIGHT, 32);

            if (ret < 0) {
              printf("Error copying image to buffer: Aborting\n");
              return -1;
            }

            buf_to_ppm(rgb_buff, WIDTH, HEIGHT, destination_frame->linesize[0],
                       "outfile1.ppm");

            Floyd_Stein_Dither(rgb_buff,
                               destination_frame->width,
                               destination_frame->height,
                               destination_frame->linesize[0], rgb_buff_size);

            while (1) ;

            }
          }
        }
      }
    }
  return 0;
}



/*
 * in order to decode a packet into a frame, you
 * need the packet, codec context, and frame
 * send the packet to the to decoder (avcodec_send_packet)
 * check response
 * if response is an err, handle
 * if response >= 0,
*/
// Finds the codec parameters, returns video_stream_index
int find_codec_parameters(AVCodecParameters** p_CodecParams, AVFormatContext* p_avformat_ctx) {
  int video_stream_index=-1;
  AVCodecParameters *p_localcodec_params; // AVCP_PTR to an AVCP_PTR
  for (unsigned int i = 0; i < p_avformat_ctx->nb_streams; i++) {

    p_localcodec_params = p_avformat_ctx->streams[i]->codecpar;
    const AVCodec* p_localcodec = avcodec_find_decoder((p_localcodec_params)->codec_id);

    if (p_localcodec == NULL) {
      printf("Error: unsupported codec");
      continue;
    }

    //printf("%d\n", p_localcodec_params->codec_id);
    if (p_localcodec_params->codec_type == AVMEDIA_TYPE_VIDEO) {
      if (video_stream_index == -1) {
        video_stream_index = i;
        *p_CodecParams = p_localcodec_params;
      }
    }
  }
  return video_stream_index;
}

void dither_buffer(uint8_t** buff, enum Dither_op dither, int width, int height) {


  /* switch(dither) { */
  /*   case FloydStein: */
  /*   { */
  /*     Floyd_Stein_Dither(buff, width, height); */
  /*     break; */
  /*   } */
  /*   case Ordered: */
  /*   { */
  /*     break; */
  /*   } */
  /*   default: */


  /* } */




}

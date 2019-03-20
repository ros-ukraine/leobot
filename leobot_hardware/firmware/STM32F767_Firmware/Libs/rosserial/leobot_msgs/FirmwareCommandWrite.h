#ifndef _ROS_leobot_msgs_FirmwareCommandWrite_h
#define _ROS_leobot_msgs_FirmwareCommandWrite_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace leobot_msgs
{

  class FirmwareCommandWrite : public ros::Msg
  {
    public:
      typedef float _motor_1_p_type;
      _motor_1_p_type motor_1_p;
      typedef float _motor_1_i_type;
      _motor_1_i_type motor_1_i;
      typedef float _motor_1_d_type;
      _motor_1_d_type motor_1_d;
      typedef float _motor_2_p_type;
      _motor_2_p_type motor_2_p;
      typedef float _motor_2_i_type;
      _motor_2_i_type motor_2_i;
      typedef float _motor_2_d_type;
      _motor_2_d_type motor_2_d;
      typedef float _motor_3_p_type;
      _motor_3_p_type motor_3_p;
      typedef float _motor_3_i_type;
      _motor_3_i_type motor_3_i;
      typedef float _motor_3_d_type;
      _motor_3_d_type motor_3_d;
      typedef float _motor_4_p_type;
      _motor_4_p_type motor_4_p;
      typedef float _motor_4_i_type;
      _motor_4_i_type motor_4_i;
      typedef float _motor_4_d_type;
      _motor_4_d_type motor_4_d;
      typedef float _motor_1_velocity_command_type;
      _motor_1_velocity_command_type motor_1_velocity_command;
      typedef float _motor_2_velocity_command_type;
      _motor_2_velocity_command_type motor_2_velocity_command;
      typedef float _motor_3_velocity_command_type;
      _motor_3_velocity_command_type motor_3_velocity_command;
      typedef float _motor_4_velocity_command_type;
      _motor_4_velocity_command_type motor_4_velocity_command;

    FirmwareCommandWrite():
      motor_1_p(0),
      motor_1_i(0),
      motor_1_d(0),
      motor_2_p(0),
      motor_2_i(0),
      motor_2_d(0),
      motor_3_p(0),
      motor_3_i(0),
      motor_3_d(0),
      motor_4_p(0),
      motor_4_i(0),
      motor_4_d(0),
      motor_1_velocity_command(0),
      motor_2_velocity_command(0),
      motor_3_velocity_command(0),
      motor_4_velocity_command(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_motor_1_p;
      u_motor_1_p.real = this->motor_1_p;
      *(outbuffer + offset + 0) = (u_motor_1_p.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_motor_1_p.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_motor_1_p.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_motor_1_p.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->motor_1_p);
      union {
        float real;
        uint32_t base;
      } u_motor_1_i;
      u_motor_1_i.real = this->motor_1_i;
      *(outbuffer + offset + 0) = (u_motor_1_i.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_motor_1_i.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_motor_1_i.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_motor_1_i.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->motor_1_i);
      union {
        float real;
        uint32_t base;
      } u_motor_1_d;
      u_motor_1_d.real = this->motor_1_d;
      *(outbuffer + offset + 0) = (u_motor_1_d.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_motor_1_d.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_motor_1_d.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_motor_1_d.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->motor_1_d);
      union {
        float real;
        uint32_t base;
      } u_motor_2_p;
      u_motor_2_p.real = this->motor_2_p;
      *(outbuffer + offset + 0) = (u_motor_2_p.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_motor_2_p.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_motor_2_p.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_motor_2_p.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->motor_2_p);
      union {
        float real;
        uint32_t base;
      } u_motor_2_i;
      u_motor_2_i.real = this->motor_2_i;
      *(outbuffer + offset + 0) = (u_motor_2_i.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_motor_2_i.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_motor_2_i.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_motor_2_i.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->motor_2_i);
      union {
        float real;
        uint32_t base;
      } u_motor_2_d;
      u_motor_2_d.real = this->motor_2_d;
      *(outbuffer + offset + 0) = (u_motor_2_d.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_motor_2_d.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_motor_2_d.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_motor_2_d.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->motor_2_d);
      union {
        float real;
        uint32_t base;
      } u_motor_3_p;
      u_motor_3_p.real = this->motor_3_p;
      *(outbuffer + offset + 0) = (u_motor_3_p.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_motor_3_p.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_motor_3_p.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_motor_3_p.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->motor_3_p);
      union {
        float real;
        uint32_t base;
      } u_motor_3_i;
      u_motor_3_i.real = this->motor_3_i;
      *(outbuffer + offset + 0) = (u_motor_3_i.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_motor_3_i.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_motor_3_i.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_motor_3_i.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->motor_3_i);
      union {
        float real;
        uint32_t base;
      } u_motor_3_d;
      u_motor_3_d.real = this->motor_3_d;
      *(outbuffer + offset + 0) = (u_motor_3_d.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_motor_3_d.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_motor_3_d.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_motor_3_d.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->motor_3_d);
      union {
        float real;
        uint32_t base;
      } u_motor_4_p;
      u_motor_4_p.real = this->motor_4_p;
      *(outbuffer + offset + 0) = (u_motor_4_p.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_motor_4_p.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_motor_4_p.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_motor_4_p.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->motor_4_p);
      union {
        float real;
        uint32_t base;
      } u_motor_4_i;
      u_motor_4_i.real = this->motor_4_i;
      *(outbuffer + offset + 0) = (u_motor_4_i.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_motor_4_i.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_motor_4_i.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_motor_4_i.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->motor_4_i);
      union {
        float real;
        uint32_t base;
      } u_motor_4_d;
      u_motor_4_d.real = this->motor_4_d;
      *(outbuffer + offset + 0) = (u_motor_4_d.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_motor_4_d.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_motor_4_d.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_motor_4_d.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->motor_4_d);
      union {
        float real;
        uint32_t base;
      } u_motor_1_velocity_command;
      u_motor_1_velocity_command.real = this->motor_1_velocity_command;
      *(outbuffer + offset + 0) = (u_motor_1_velocity_command.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_motor_1_velocity_command.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_motor_1_velocity_command.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_motor_1_velocity_command.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->motor_1_velocity_command);
      union {
        float real;
        uint32_t base;
      } u_motor_2_velocity_command;
      u_motor_2_velocity_command.real = this->motor_2_velocity_command;
      *(outbuffer + offset + 0) = (u_motor_2_velocity_command.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_motor_2_velocity_command.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_motor_2_velocity_command.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_motor_2_velocity_command.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->motor_2_velocity_command);
      union {
        float real;
        uint32_t base;
      } u_motor_3_velocity_command;
      u_motor_3_velocity_command.real = this->motor_3_velocity_command;
      *(outbuffer + offset + 0) = (u_motor_3_velocity_command.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_motor_3_velocity_command.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_motor_3_velocity_command.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_motor_3_velocity_command.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->motor_3_velocity_command);
      union {
        float real;
        uint32_t base;
      } u_motor_4_velocity_command;
      u_motor_4_velocity_command.real = this->motor_4_velocity_command;
      *(outbuffer + offset + 0) = (u_motor_4_velocity_command.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_motor_4_velocity_command.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_motor_4_velocity_command.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_motor_4_velocity_command.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->motor_4_velocity_command);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_motor_1_p;
      u_motor_1_p.base = 0;
      u_motor_1_p.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_motor_1_p.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_motor_1_p.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_motor_1_p.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->motor_1_p = u_motor_1_p.real;
      offset += sizeof(this->motor_1_p);
      union {
        float real;
        uint32_t base;
      } u_motor_1_i;
      u_motor_1_i.base = 0;
      u_motor_1_i.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_motor_1_i.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_motor_1_i.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_motor_1_i.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->motor_1_i = u_motor_1_i.real;
      offset += sizeof(this->motor_1_i);
      union {
        float real;
        uint32_t base;
      } u_motor_1_d;
      u_motor_1_d.base = 0;
      u_motor_1_d.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_motor_1_d.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_motor_1_d.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_motor_1_d.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->motor_1_d = u_motor_1_d.real;
      offset += sizeof(this->motor_1_d);
      union {
        float real;
        uint32_t base;
      } u_motor_2_p;
      u_motor_2_p.base = 0;
      u_motor_2_p.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_motor_2_p.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_motor_2_p.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_motor_2_p.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->motor_2_p = u_motor_2_p.real;
      offset += sizeof(this->motor_2_p);
      union {
        float real;
        uint32_t base;
      } u_motor_2_i;
      u_motor_2_i.base = 0;
      u_motor_2_i.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_motor_2_i.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_motor_2_i.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_motor_2_i.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->motor_2_i = u_motor_2_i.real;
      offset += sizeof(this->motor_2_i);
      union {
        float real;
        uint32_t base;
      } u_motor_2_d;
      u_motor_2_d.base = 0;
      u_motor_2_d.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_motor_2_d.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_motor_2_d.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_motor_2_d.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->motor_2_d = u_motor_2_d.real;
      offset += sizeof(this->motor_2_d);
      union {
        float real;
        uint32_t base;
      } u_motor_3_p;
      u_motor_3_p.base = 0;
      u_motor_3_p.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_motor_3_p.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_motor_3_p.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_motor_3_p.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->motor_3_p = u_motor_3_p.real;
      offset += sizeof(this->motor_3_p);
      union {
        float real;
        uint32_t base;
      } u_motor_3_i;
      u_motor_3_i.base = 0;
      u_motor_3_i.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_motor_3_i.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_motor_3_i.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_motor_3_i.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->motor_3_i = u_motor_3_i.real;
      offset += sizeof(this->motor_3_i);
      union {
        float real;
        uint32_t base;
      } u_motor_3_d;
      u_motor_3_d.base = 0;
      u_motor_3_d.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_motor_3_d.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_motor_3_d.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_motor_3_d.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->motor_3_d = u_motor_3_d.real;
      offset += sizeof(this->motor_3_d);
      union {
        float real;
        uint32_t base;
      } u_motor_4_p;
      u_motor_4_p.base = 0;
      u_motor_4_p.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_motor_4_p.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_motor_4_p.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_motor_4_p.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->motor_4_p = u_motor_4_p.real;
      offset += sizeof(this->motor_4_p);
      union {
        float real;
        uint32_t base;
      } u_motor_4_i;
      u_motor_4_i.base = 0;
      u_motor_4_i.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_motor_4_i.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_motor_4_i.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_motor_4_i.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->motor_4_i = u_motor_4_i.real;
      offset += sizeof(this->motor_4_i);
      union {
        float real;
        uint32_t base;
      } u_motor_4_d;
      u_motor_4_d.base = 0;
      u_motor_4_d.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_motor_4_d.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_motor_4_d.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_motor_4_d.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->motor_4_d = u_motor_4_d.real;
      offset += sizeof(this->motor_4_d);
      union {
        float real;
        uint32_t base;
      } u_motor_1_velocity_command;
      u_motor_1_velocity_command.base = 0;
      u_motor_1_velocity_command.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_motor_1_velocity_command.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_motor_1_velocity_command.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_motor_1_velocity_command.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->motor_1_velocity_command = u_motor_1_velocity_command.real;
      offset += sizeof(this->motor_1_velocity_command);
      union {
        float real;
        uint32_t base;
      } u_motor_2_velocity_command;
      u_motor_2_velocity_command.base = 0;
      u_motor_2_velocity_command.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_motor_2_velocity_command.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_motor_2_velocity_command.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_motor_2_velocity_command.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->motor_2_velocity_command = u_motor_2_velocity_command.real;
      offset += sizeof(this->motor_2_velocity_command);
      union {
        float real;
        uint32_t base;
      } u_motor_3_velocity_command;
      u_motor_3_velocity_command.base = 0;
      u_motor_3_velocity_command.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_motor_3_velocity_command.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_motor_3_velocity_command.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_motor_3_velocity_command.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->motor_3_velocity_command = u_motor_3_velocity_command.real;
      offset += sizeof(this->motor_3_velocity_command);
      union {
        float real;
        uint32_t base;
      } u_motor_4_velocity_command;
      u_motor_4_velocity_command.base = 0;
      u_motor_4_velocity_command.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_motor_4_velocity_command.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_motor_4_velocity_command.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_motor_4_velocity_command.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->motor_4_velocity_command = u_motor_4_velocity_command.real;
      offset += sizeof(this->motor_4_velocity_command);
     return offset;
    }

    const char * getType(){ return "leobot_msgs/FirmwareCommandWrite"; };
    const char * getMD5(){ return "3fc1e386055fce07b1eb02500bb1ca44"; };

  };

}
#endif
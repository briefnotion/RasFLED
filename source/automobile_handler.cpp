// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: automobile_handler.cpp
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2858 Core Dynamics
// ***************************************************************************************

#ifndef AUTOMOBILE_HANDLER_CPP
#define AUTOMOBILE_HANDLER_CPP

#include "automobile_handler.h"

using namespace std;

// -------------------------------------------------------------------------------------

void AUTOMOBILE_HANDLER::alert(system_data &sdSysData, ANIMATION_HANDLER &Animations, unsigned long tmeCurrentTime)
{
  if (ALERT_TIMER.ping_down(tmeCurrentTime) == false)
  {
    Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "FLASH");
    ALERT_TIMER.ping_up(tmeCurrentTime, 10000);
  }
}

void AUTOMOBILE_HANDLER::update_events(system_data &sdSysData, ANIMATION_HANDLER &Animations, unsigned long tmeCurrentTime)
{
  // -------------------------------------------------------------------------------------
  // Automobile Data Switched to Not Available

  // Check for changes in the automobile availability
  if ((set_bool_with_change_notify(sdSysData.CAR_INFO.active(), AUTO_ACTIVE) == true))
  {
    if (sdSysData.CAR_INFO.active() == false)
    {
      // if automobile is no longer available, make sure all related lights are off.
      Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "Automobile - Gear Select_Park_Off");
      Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "Automobile - Gear Select_Neutral_Off");
      Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "Automobile - Gear Select_Reverse_Off");
      Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "Automobile - Gear Select_Drive_Off");
      Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "Automobile - Velocity_Off");
      Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "Automobile - Door Handle Running Off");

      GEAR_PARK = false;
      GEAR_NEUTRAL = false;
      GEAR_REVERSE = false;
      GEAR_DRIVE = false;
      LIGHT_VELOCITY_ON = false;
      LIGHT_DOOR_HANDLE_ON = false;
    }
  }

  // -------------------------------------------------------------------------------------
  // Automobile Data Available
  if (sdSysData.CAR_INFO.active() == true)
  {
    // Gear Selection

    // Changing Gear to Park
    if (set_bool_with_change_notify(sdSysData.CAR_INFO.STATUS.GEAR.gear_selection_park(), GEAR_PARK) == true)
    {
      if (GEAR_PARK == true)
      {
        // Call animation to turn on Park color.
        Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "Automobile - Gear Select_Park_On");
      }
      else
      {
        // Call animation to turn off Park color.
        Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "Automobile - Gear Select_Park_Off");        
      }
    }
    
    // Changing Gear to Neutral
    if (set_bool_with_change_notify(sdSysData.CAR_INFO.STATUS.GEAR.gear_selection_neutral(), GEAR_NEUTRAL) == true)
    {
      if (GEAR_NEUTRAL == true)
      {
        // Call animation to turn on Neutral color.
        Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "Automobile - Gear Select_Neutral_On");
      }
      else
      {
        // Call animation to turn off Neutral color.
        Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "Automobile - Gear Select_Neutral_Off");        
      }
    }

    // Changing Gear to Reverse
    if (set_bool_with_change_notify(sdSysData.CAR_INFO.STATUS.GEAR.gear_selection_reverse(), GEAR_REVERSE) == true)
    {
      if (GEAR_REVERSE == true)
      {
        // Call animation to turn on Reverse color.
        Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "Automobile - Gear Select_Reverse_On");
      }
      else
      {
        // Call animation to turn off Reverse color.
        Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "Automobile - Gear Select_Reverse_Off");        
      }
    }

    // Changing Gear to Drive
    if (set_bool_with_change_notify(sdSysData.CAR_INFO.STATUS.GEAR.gear_selection_drive() || 
                                    sdSysData.CAR_INFO.STATUS.GEAR.gear_selection_low(), GEAR_DRIVE) == true)
    {
      if (GEAR_DRIVE == true)
      {
        // Call animation to turn on Drive color.
        Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "Automobile - Gear Select_Drive_On");
      }
      else
      {
        // Call animation to turn off Drive color.
        Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "Automobile - Gear Select_Drive_Off");
      }
    }

    // -------------------------------------------------------------------------------------
    // While Driving
    float multiplier = 0;
    float multiplier_caution = 0;

    const int activate_speed = 10;
    const int caution_speed = 5;

    // -------------------------------------------------------------------------------------
    // Alerts at non stops at low speed
    
    // Alert if door is open
    if (sdSysData.CAR_INFO.STATUS.SPEED.SPEED_TRANS.val_mph() > 0 && 
        sdSysData.CAR_INFO.STATUS.SPEED.SPEED_TRANS.val_mph() < 5)
    {
      if (sdSysData.CAR_INFO.STATUS.DOORS.hatchback_door_open() == true ||
          sdSysData.CAR_INFO.STATUS.DOORS.hood_door_open() == true ||
          sdSysData.CAR_INFO.STATUS.DOORS.lb_door_open() == true ||
          sdSysData.CAR_INFO.STATUS.DOORS.lf_door_open() == true ||
          sdSysData.CAR_INFO.STATUS.DOORS.rb_door_open() == true ||
          sdSysData.CAR_INFO.STATUS.DOORS.rf_door_open() == true)
      {
        alert(sdSysData, Animations, tmeCurrentTime);
      }

      // Alert if only parking lights are on
      if (sdSysData.CAR_INFO.STATUS.INDICATORS.val_lights_pos() == 1)
      {
          alert(sdSysData, Animations, tmeCurrentTime);
      }
    }

    // -------------------------------------------------------------------------------------
    // Lights
    
    // Turn off lights if speed over set value.
    if (sdSysData.CAR_INFO.STATUS.SPEED.SPEED_TRANS.val_mph() > activate_speed + 6)
    {
      if (LIGHT_DOOR_HANDLE_ON == true)
      {
        Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "Automobile - Door Handle Running Off");
        LIGHT_DOOR_HANDLE_ON = false;
      }

      if (LIGHT_DRIVE_ON == true)
      {
        Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "Automobile - Gear Select_Drive_Off");
        LIGHT_DRIVE_ON = false;
      }

      if (LIGHT_VELOCITY_ON == true)
      {
        Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "Automobile - Velocity_Off");
        LIGHT_VELOCITY_ON = false;
      }
    }

    // -------------------------------------------------------------------------------------
    // Turn on lights if speed under set value.
    else if (sdSysData.CAR_INFO.STATUS.SPEED.SPEED_TRANS.val_mph() < activate_speed + 4)
    {
      if (LIGHT_DOOR_HANDLE_ON == false)
      {
        Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "Automobile - Door Handle Running On");
        LIGHT_DOOR_HANDLE_ON = true;
      }

      if (LIGHT_DRIVE_ON == false)
      {
        Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "Automobile - Gear Select_Drive_On");
        LIGHT_DRIVE_ON = true;
      }

      if (set_bool_with_change_notify((GEAR_DRIVE == true || GEAR_NEUTRAL == true), LIGHT_VELOCITY_ON) == true)
      {
        if (LIGHT_VELOCITY_ON == true)
        {
          Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "Automobile - Velocity_On");
        }
        else
        {
          Animations.call_animation(sdSysData, tmeCurrentTime, "Car", "Automobile - Velocity_Off");
        }
      }

      // Set colors if Velocity lights are on.  They could be off if in reverse or park.
      if (LIGHT_VELOCITY_ON == true)
      {
        // Multiplier
        if (sdSysData.CAR_INFO.STATUS.SPEED.SPEED_TRANS.val_mph() < activate_speed)
        {
          multiplier = 1 - sdSysData.CAR_INFO.STATUS.SPEED.SPEED_TRANS.val_mph() / activate_speed;
        }
        else 
        {
          multiplier = 0;
        }
        
        // Caution Multiplier
        if (sdSysData.CAR_INFO.STATUS.SPEED.SPEED_TRANS.val_mph() < caution_speed)
        {
          multiplier_caution = 1 - sdSysData.CAR_INFO.STATUS.SPEED.SPEED_TRANS.val_mph() / caution_speed;
        }
        else 
        {
          multiplier_caution = 0;
        }

        CRGB drive_color = CRGB(32, (int)(16 * multiplier_caution), 0);
        CRGB velocity_color = CRGB(8, 0, 0);
        CRGB drive_pulse_color = CRGB(30, 30, 30);

        // Adjust light colors and atttributes
        // Gear
        Animations.mod_run_anim_color_dest_1("AUGEAR_DRIVE_O", drive_color.brightness(multiplier));
        Animations.mod_run_anim_color_dest_1("AUGEAR_DRIVE_D", drive_color.brightness(multiplier));

        // Velocity
        Animations.mod_run_anim_color_dest_1("AUGEAR_VELOCITY_D", velocity_color.brightness(multiplier));
        Animations.mod_run_anim_color_dest_1("AUGEAR_VELOCITY_O", velocity_color.brightness(multiplier));

        Animations.mod_run_anim_velocity("AUGEAR_VELOCITY_D", sdSysData.CAR_INFO.STATUS.SPEED.SPEED_TRANS.val_mph());
        Animations.mod_run_anim_velocity("AUGEAR_VELOCITY_O", sdSysData.CAR_INFO.STATUS.SPEED.SPEED_TRANS.val_mph());

        // Keep?
        Animations.mod_run_anim_color_dest_1("AUGEAR_DRIVE_PULSE", drive_pulse_color.brightness(multiplier));
        Animations.mod_run_anim_color_dest_1("AUGEAR_DRIVE_PULSE", drive_pulse_color.brightness(multiplier));
      }
    }
  }
}

// -------------------------------------------------------------------------------------

#endif

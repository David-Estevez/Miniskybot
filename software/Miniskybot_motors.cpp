//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//-- Miniskybot library
//------------------------------------------------------------------------------
//-- Simplify working and programming a Miniskybot (or similar) robot by using
//-- this library.
//--
//-- This library takes charge of controlling the motors by means of a L293 dual
//-- H-bridge circuit, but extra functions could be added to work with more types
//-- of motors.
//--
//-- For more info, read README
//------------------------------------------------------------------------------
//-- Author:
//-- David Estévez-Fernández, Jun 2012
//-- GPL license
//------------------------------------------------------------------------------
//-- Requires a Miniskybot  robot, design by Juan González-Gómez (Obijuan):
//-- https://github.com/Obijuan/Miniskybot
//------------------------------------------------------------------------------


#include "Miniskybot_motors.h"


//-------------------------------------------------------------------------
//-- Constructor
//-------------------------------------------------------------------------
//-- Arguments: pins conected to the H-bridge (left, right and chip enable)
//-------------------------------------------------------------------------

MotorL293::MotorL293( )
{
	_pinLeft = -1;
	_pinRight = -1;
	_pinEnable = -1;

	_speed = 0;
	_forward = true;
}


//--------------------------------------
//-- Initialize the motor object:
//--------------------------------------

void MotorL293::attach(int pinLeft, int pinRight, int pinEnable)
{
	//-- Save the pin configuration
	_pinLeft = pinLeft;
	_pinRight = pinRight;
	_pinEnable = pinEnable;

	//-- Set the pins as outputs
	pinMode( _pinLeft, OUTPUT);
	pinMode( _pinRight, OUTPUT);
	pinMode( _pinEnable, OUTPUT);

	//-- Put all pins at 0V (motor OFF)
	digitalWrite( _pinLeft, LOW);
	digitalWrite( _pinRight, LOW);
	digitalWrite( _pinEnable, LOW );
}


//---------------------------------------------------------
//-- Sets motor velocity to a value between 0 and 255.
//-- Sense is given by the sign of velocity.
//---------------------------------------------------------

void MotorL293::setVelocity( int velocity)
{
	//-- If pins are not assigned, don't execute any code
	if ( _pinLeft != -1 && _pinRight != -1 && _pinEnable != -1)
	{
		//-- Distinguish between forward / backwards movement
		if ( velocity >= 0 )
		{
			//-- Assign new values to variables:
			_speed = velocity;
			_forward = true;
		
			//-- Send the correct signals to the H-bridge:
			digitalWrite( _pinLeft, LOW);
			digitalWrite( _pinRight, HIGH);
		}
		else
		{
			//-- Assign new values to variables:
			_speed = -velocity;
			_forward = false;

			//-- Send the correct signals to the H-bridge:	
			digitalWrite( _pinLeft, HIGH);
			digitalWrite( _pinRight, LOW);
		}

		//-- Set speed:
		analogWrite(  _pinEnable, _speed);
	}
}


//---------------------------------------------------------
//-- Sets motor velocity to a value between 0 and 255.
//-- Sense is given explicitely by forward, velocity
//-- should be positive.
//---------------------------------------------------------

void MotorL293::setVelocity( int velocity, bool forward)
{
	//-- If pins are not assigned, don't execute any code
	if ( _pinLeft != -1 && _pinRight != -1 && _pinEnable != -1)
	{
		//-- Assign new values to variables:
		_speed = abs(velocity);		
		_forward = forward;
	
	
		//-- Send the correct signals to the H-bridge:
		if ( _forward )
		{				
			digitalWrite( _pinLeft, LOW);
			digitalWrite( _pinRight, HIGH);
		}
		else
		{
			digitalWrite( _pinLeft, HIGH);
			digitalWrite( _pinRight, LOW);
		}

		//-- Set speed:
		analogWrite(  _pinEnable, _speed);
	} 
}


//----------------------------------------------------
//-- Returns the value of the current velocity
//-- (not actual velocity, the one given by the user)
//----------------------------------------------------

int MotorL293::getVelocity()
{
	//-- Set the modulus:
	int velocity = _speed;
	
	//-- Set the sense:
	if ( !_forward) {velocity*=-1;}
	
	return velocity;
}



//----------------------------------------------------
//-- Just stops the motor
//----------------------------------------------------

void MotorL293::emergencyBrake()
{
	//-- Stop the motor
	digitalWrite( _pinEnable, LOW);	
	digitalWrite( _pinLeft, HIGH);
	digitalWrite( _pinRight, HIGH);
}
//#######################################################//

Servos::Servos( )
{
    _pin = -1;
    _type = -1;

    _speed = 0;
    _forward = true;
}


//--------------------------------------
//-- Initialize the motor object:
//--------------------------------------

void Servos::attach(int pin, int type)
{
    //-- Save the pin configuration
    _pin = pin;
    _type = type;
    _servo.attach(_pin);
}


//---------------------------------------------------------
//-- Sets motor velocity to a value between 0 and 255.
//-- Sense is given by the sign of velocity.
//---------------------------------------------------------

void Servos::setVelocity( int velocity)
{
    //-- If pins are not assigned, don't execute any code
    if ( _pin != -1 && _type != -1)
    {
        //-- Distinguish between forward / backwards movement
        if ( velocity > 0 )
        {
            //-- Assign new values to variables:
            if (_type==0){
                _speed = -velocity;
            }
            else{
                _speed = velocity;
            }
            _forward = true;

        }
        else if( velocity < 0 )
        {
            //-- Assign new values to variables:
            if (_type==1){
                _speed = velocity;
            }
            else{
                _speed = -velocity;
            }
            _forward = false;
        }
        else if(velocity == 0){
            _servo.detach();
        }
        //-- Set speed:
        _servo.attach(_pin);
        _servo.write(map(_speed,-10,10,0,180));
    }
}


//---------------------------------------------------------
//-- Sets motor velocity to a value between 0 and 255.
//-- Sense is given explicitely by forward, velocity
//-- should be positive.
//---------------------------------------------------------

void Servos::setVelocity( int velocity, bool forward)
{
    //-- If pins are not assigned, don't execute any code
    if ( _pin != -1 && _pin != -1 && _pin != -1)
    {
        //-- Assign new values to variables:
        _speed = abs(velocity);
        _forward = forward;


        //-- Send the correct signals to the H-bridge:
        if ( _forward )
        {
            digitalWrite( _pin, LOW);
            digitalWrite( _pin, HIGH);
        }
        else
        {
            digitalWrite( _pin, HIGH);
            digitalWrite( _pin, LOW);
        }

        //-- Set speed:
        analogWrite(  _pin, _speed);
    }
}






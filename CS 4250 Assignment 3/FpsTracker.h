/*************************************************************************************

Program:			CS 4250 Assignment 3: 3D Roller Coaster

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Interface file for the FpsTracker class. This is a static class
					that is responsible for keeping track of the game FPS as well as
					the elapsed ms since the last update (FrameTimeMs) which is used
					to scale all movement and time related things in the game.

Date:				November 9, 2015

*************************************************************************************/

#ifndef FPSTRACKER_H
#define FPSTRACKER_H

namespace Bagnall
{
	class FpsTracker
	{
	public:
		/**********************************************************************
		Function:		Update
		Purpose:		Update the FpsTracker. Updates FrameTimeMs and keeps
						track of the FPS.
		**********************************************************************/
		static void Update();

		/**********************************************************************
		Function:		GetFrameTimeMs
		Purpose:		Static getter for frameTimeMs.
		**********************************************************************/
		static int GetFrameTimeMs();

		/**********************************************************************
		Function:		GetFps
		Purpose:		Static getter for fps.
		**********************************************************************/
		static int GetFps();
	private:
		static int last_frame_time, // timestamp of the previous frame
			frame_counter, // frame counter for tracking fps
			frame_time_accum, // time accumulator for tracking fps
			fps, // frames per second
			frameTimeMs; // elapsed milliseconds since previous frame
	};
}

#endif

﻿using System;

namespace Billiards
{
	public static class BilliardsTask
	{
		public static double BounceWall(double directionRadians, double wallInclinationRadians)
		{
          

             return ((wallInclinationRadians) *2 - directionRadians);
          
        }
	}
}
/*!
 * \file galileo_navigation_message.h
 * \brief  Implementation of a Galileo NAV Data message decoder as described in Galileo ICD
 * \author Mara Branzanti 2013. mara.branzanti(at)gmail.com
 * \author Javier Arribas, 2013. jarribas(at)cttc.es
 *
 * -------------------------------------------------------------------------
 *
 * Copyright (C) 2010-2013  (see AUTHORS file for a list of contributors)
 *
 * GNSS-SDR is a software defined Global Navigation
 *          Satellite Systems receiver
 *
 * This file is part of GNSS-SDR.
 *
 * GNSS-SDR is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * at your option) any later version.
 *
 * GNSS-SDR is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNSS-SDR. If not, see <http://www.gnu.org/licenses/>.
 *
 * -------------------------------------------------------------------------
 */

#ifndef GNSS_SDR_GALILEO_NAVIGATION_MESSAGE_H_
#define GNSS_SDR_GALILEO_NAVIGATION_MESSAGE_H_

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <bitset>
#include <boost/assign.hpp>
#include <boost/cstdint.hpp>  // for boost::uint16_t
#include <cmath>
#include <utility>

// Galileo Navigation Message structures
#include "galileo_ephemeris.h"
#include "galileo_iono.h"
#include "galileo_almanac.h"
#include "galileo_utc_model.h"

#include "Galileo_E1.h"



class Galileo_Navigation_Message {

private:


	bool CRC_test(std::bitset<GALILEO_DATA_FRAME_BITS> bits,boost::uint32_t checksum);
	bool read_navigation_bool(std::bitset<GALILEO_DATA_JK_BITS> bits, const std::vector<std::pair<int,int> > parameter);
	//void print_galileo_word_bytes(unsigned int GPS_word);
	unsigned long int read_navigation_unsigned(std::bitset<GALILEO_DATA_JK_BITS> bits, const std::vector< std::pair<int,int> > parameter);
	unsigned long int read_page_type_unsigned(std::bitset<GALILEO_PAGE_TYPE_BITS> bits, const std::vector< std::pair<int,int> > parameter);
	signed long int read_navigation_signed(std::bitset<GALILEO_DATA_JK_BITS> bits, const std::vector<std::pair<int,int> > parameter);

	int x,y;

public:
	int flag_even_word;

	/*Word type 1: Ephemeris (1/4)*/
		int IOD_nav_1;  // IOD_nav page 1
		double t0e_1; 	// Ephemeris reference time [s]
		double M0_1;		// Mean anomaly at reference time [semi-circles]
		double e_1;		// Eccentricity
		double A_1;   	// Square root of the semi-major axis [metres^1/2]

		/*Word type 2: Ephemeris (2/4)*/
		int IOD_nav_2;  // IOD_nav page 2
		double OMEGA_0_2; // Longitude of ascending node of orbital plane at weekly epoch [semi-circles]
		double i_0_2;     // Inclination angle at reference time  [semi-circles]
		double omega_2;   // Argument of perigee [semi-circles]
		double iDot_2;    // Rate of inclination angle [semi-circles/sec]

		/*Word type 3: Ephemeris (3/4) and SISA*/
		int IOD_nav_3;  		//
		double OMEGA_dot_3;		// Rate of right ascension [semi-circles/sec]
		double delta_n_3;		// Mean motion difference from computed value  [semi-circles/sec]
		double C_uc_3;			// Amplitude of the cosine harmonic correction term to the argument of latitude [radians]
		double C_us_3;			// Amplitude of the sine harmonic correction term to the argument of latitude [radians]
		double C_rc_3;			// Amplitude of the cosine harmonic correction term to the orbit radius [meters]
		double C_rs_3;			// Amplitude of the sine harmonic correction term to the orbit radius [meters]
		double SISA_3;			//

		/*Word type 4: Ephemeris (4/4) and Clock correction parameters*/
		int IOD_nav_4;		//
		int SV_ID_PRN_4;		//
		double C_ic_4;		// Amplitude of the cosine harmonic correction 	term to the angle of inclination [radians]
		double C_is_4;		// Amplitude of the sine harmonic correction term to the angle of inclination [radians]
		/*Clock correction parameters*/
		double t0c_4;			//Clock correction data reference Time of Week [sec]
		double af0_4;			//SV clock bias correction coefficient [s]
		double af1_4;			//SV clock drift correction coefficient [s/s]
		double af2_4;			//SV clock drift rate correction coefficient [s/s^2]
		double spare_4;


		/*Word type 5: Ionospheric correction, BGD, signal health and data validity status and GST*/
		/*Ionospheric correction*/
		/*Az*/
		double ai0_5;		//Effective Ionisation Level 1st order parameter [sfu]
		double ai1_5;		//Effective Ionisation Level 2st order parameter [sfu/degree]
		double ai2_5;		//Effective Ionisation Level 3st order parameter [sfu/degree]

		/*Ionospheric disturbance flag*/
		bool Region1_flag_5;	// Ionospheric Disturbance Flag for region 1
		bool Region2_flag_5;	// Ionospheric Disturbance Flag for region 2
		bool Region3_flag_5;	// Ionospheric Disturbance Flag for region 3
		bool Region4_flag_5;	// Ionospheric Disturbance Flag for region 4
		bool Region5_flag_5;	// Ionospheric Disturbance Flag for region 5
		double BGD_E1E5a_5;	//E1-E5a Broadcast Group Delay [s]
		double BGD_E1E5b_5;	//E1-E5b Broadcast Group Delay [s]

		double E5b_HS_5;		//
		double E1B_HS_5;		//
		double E5b_DVS_5;	//
		double E1B_DVS_5;	//
		/*GST*/
		double WN_5;
		double TOW_5;

		double spare_5;
		/*Word type 6: GST-UTC conversion parameters*/

			double A0_6;
			double A1_6;
			double Delta_tLS_6;
			double t0t_6;
			double WNot_6;
			double WN_LSF_6;
			double DN_6;
			double Delta_tLSF_6;
			double TOW_6;

			/*Word type 7: Almanac for SVID1 (1/2), almanac reference time and almanac reference week number*/
			int IOD_a_7;
			double WN_a_7;
			double t0a_7;
			int SVID1_7;
			double Delta_alpha_7;
			double e_7;
			double omega_7;
			double delta_i_7;
			double Omega0_7;
			double Omega_dot_7;
			double M0_7;

			/*Word type 8: Almanac for SVID1 (2/2) and SVID2 (1/2)*/
			int IOD_a_8;
			double af0_8;
			double af1_8;
			double E5b_HS_8;
			double E1B_HS_8;
			int SVID2_8;
			double DELTA_A_8;
			double e_8;
			double omega_8;
			double delta_i_8;
			double Omega0_8;
			double Omega_dot_8;

			/*Word type 9: Almanac for SVID2 (2/2) and SVID3 (1/2)*/

			int IOD_a_9;
			double WN_a_9;
			double t0a_9;
			double M0_9;
			double af0_9;
			double af1_9;
			double E5b_HS_9;
			double E1B_HS_9;
			int SVID3_9;
			double DELTA_A_9;
			double e_9;
			double omega_9;
			double delta_i_9;


			/*Word type 10: Almanac for SVID3 (2/2) and GST-GPS conversion parameters*/

			int IOD_a_10;
			double Omega0_10;
			double Omega_dot_10;
			double M0_10;
			double af0_10;
			double af1_10;
			double E5b_HS_10;
			double E1B_HS_10;
			double A_0G_10;
			double A_1G_10;
			double t_0G_10;
			double WN_0G_10;



			/*Word type 0: I/NAV Spare Word*/
			double Time_0;
			double WN_0;
			double TOW_0;


	/*
	 * \brief Takes in input a page (Odd or Even) of 120 bit, split it according ICD 4.3.2.3 and join Data_k with Data_j
	 */
	void split_page(const char *page, int flag_even_word);
	/*
	 * \brief Takes in input Data_jk (128 bit) and split it in ephemeris parameters according ICD 4.3.5
	 */
	int page_jk_decoder(char *data_jk);


	/*
	 * \brief Write doxigen function description here
	 */

	void reset();

	/*
	 * \brief Returns true if new Ephemeris has arrived. The flag is set to false when the function is executed
	 */
	bool have_new_ephemeris();
	/*
	 * \brief Returns true if new Iono model has arrived. The flag is set to false when the function is executed
	 */
	bool have_new_iono();
	/*
	 * \brief Returns true if new UTC model has arrived. The flag is set to false when the function is executed
	 */
	bool have_new_utc_model();

	/*
	 * \brief Returns true if new UTC model has arrived. The flag is set to false when the function is executed
	 */
	bool have_new_almanac();


	/*
	 * \brief Returns a Galileo_Ephemeris object filled with the latest navigation data received
	 */
	Galileo_Ephemeris get_ephemeris();

	/*
	 * \brief Returns a Galileo_Iono object filled with the latest navigation data received
	 */
	Galileo_Iono get_iono();

	/*
	 * \brief Returns a Galileo_Utc_Model object filled with the latest navigation data received
	 */
	Galileo_Utc_Model get_utc_model();

	/*
	 * \brief Returns a Galileo_Almanac object filled with the latest navigation data received
	 */
	Galileo_Almanac get_almanac();


	Galileo_Navigation_Message();
};

#endif /* GALILEO_NAVIGATION_MESSAGE_H_ */
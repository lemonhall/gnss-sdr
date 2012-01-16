/*!
 * \file gnss_satellite.cc
 * \brief  Implementation of the Gnss_Satellite class
 * \author Carles Fernandez-Prades, 2012. cfernandez(at)cttc.es
 *
 * -------------------------------------------------------------------------
 *
 * Copyright (C) 2010-2012  (see AUTHORS file for a list of contributors)
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
#include "gnss_satellite.h"
#include <glog/log_severity.h>
#include <glog/logging.h>



Gnss_Satellite::Gnss_Satellite()
{
    Gnss_Satellite::reset();
}




Gnss_Satellite::Gnss_Satellite(std::string system_, unsigned int PRN_)
{
    Gnss_Satellite::reset();
    Gnss_Satellite::set_system(system_);
    Gnss_Satellite::set_PRN(PRN_);
    Gnss_Satellite::set_block(system_, PRN_);
}




Gnss_Satellite::~Gnss_Satellite()
{}





void Gnss_Satellite::reset()
{
    system_set = {"GPS", "GLONASS", "SBAS", "Galileo", "Compass"};
    PRN = 0;
    system = std::string("");
    block = std::string("");
}





void Gnss_Satellite::set_system(std::string system_)
{
    // Set the satellite system {"GPS", "GLONASS", "SBAS", "Galileo", "Compass"}
    std::set<std::string>::iterator it = system_set.find(system_);

    if(it != system_set.end())
        {
            system = system_;
        }
    else
        {
            LOG_AT_LEVEL(ERROR) << "System " << system_ << " is not defined {GPS, GLONASS, SBAS, Galileo, Compass}";
            system =  std::string("");
        }
}




void Gnss_Satellite::set_PRN(unsigned int PRN_)
{
    // Set satellite's PRN
    if (system.compare("") == 0)
        {
            LOG_AT_LEVEL(ERROR) << "Trying to define PRN while system is not defined";
            PRN = 0;
        }
    if (system.compare("GPS") == 0)
        {
            if (PRN_ < 1 or PRN > 32)
                {
                    LOG_AT_LEVEL(ERROR) << "This PRN is not defined";
                    PRN = 0;
                }
            else
                {
                    PRN = PRN_;
                }
        }
    else if (system.compare("Glonass") == 0)
           {
               if (PRN_ < 1 or PRN > 24)
                   {
                       LOG_AT_LEVEL(ERROR) << "This PRN is not defined";
                       PRN = 0;
                   }
               else
                   {
                       PRN = PRN_;
                   }
           }
    else if (system.compare("SBAS") == 0)
        {
            if (PRN_ == 122){ PRN = PRN_; }        // WAAS Inmarsat 3F4 (AOR-W)
            else if (PRN_ == 134){ PRN = PRN_; }   // WAAS Inmarsat 3F3 (POR)
            else if (PRN_ == 120){ PRN = PRN_; }   // EGNOS AOR-E Broadcast satellite http://www.egnos-pro.esa.int/index.html
            else if (PRN_ == 124){ PRN = PRN_; }   // EGNOS ESA ARTEMIS used for EGNOS Operations
            else if (PRN_ == 126){ PRN = PRN_; }   // EGNOS IOR-W  currently used by Industry to perform various tests on the system.
            else
                {
                    LOG_AT_LEVEL(ERROR) << "This PRN is not defined";
                    PRN = 0;
                }
        }
    else if (system.compare("Galileo") == 0)
            {
                if (PRN_ == 11)
                    {
                        PRN = 11;
                    }
                else
                    {
                        LOG_AT_LEVEL(ERROR) << "This PRN is not defined";
                        PRN = 0;
                    }
            }
    else
        {
            LOG_AT_LEVEL(ERROR) << "System " << system << " is not defined";
            PRN = 0;
        }
}





unsigned int Gnss_Satellite::get_PRN()
{
    // Get satellite's PRN
    unsigned int PRN_;
    PRN_ = PRN;
    return PRN_;
}






std::string Gnss_Satellite::get_system()
{
    // Get the satellite system {"GPS", "GLONASS", "SBAS", "Galileo", "Compass"}
    std::string system_;
    system_ = system;
    return system_;
}





std::string Gnss_Satellite::get_block()
{
    // Get the satellite block
    std::string block_;
    block_ = block;
    return block_;
}







void Gnss_Satellite::set_block(std::string system_, unsigned int PRN_ )
{
    if (system_.compare("GPS") == 0)
        {
            switch ( PRN_ )
            {
            // info from http://www.navcen.uscg.gov/?Do=constellationStatus

            case 1 :
                block = std::string("IIF");   //Plane D
                break;
            case 2 :
                block = std::string("IIR");   //Plane D
                break;
            case 3 :
                block = std::string("IIA");   //Plane D
                break;
            case 4 :
                block = std::string("IIA");   //Plane D
                break;
            case 5 :
                block = std::string("IIR-M"); //Plane F
                break;
            case 6 :
                block = std::string("IIA");   //Plane C
                break;
            case 7 :
                block = std::string("IIR-M"); //Plane A
                break;
            case 8 :
                block = std::string("IIA");   //Plane A
                break;
            case 9 :
                block = std::string("IIA");   //Plane A
                break;
            case 10 :
                block = std::string("IIA");   //Plane E
                break;
            case 11 :
                block = std::string("IIR");   //Plane D
                break;
            case 12 :
                block = std::string("IIR-M"); //Plane B
                break;
            case 13 :
                block = std::string("IIR");   //Plane F
                break;
            case 14 :
                block = std::string("IIR");   //Plane F
                break;
            case 15 :
                block = std::string("IIR-M"); //Plane F
                break;
            case 16 :
                block = std::string("IIR");   //Plane B
                break;
            case 17 :
                block = std::string("IIR-M"); //Plane C
                break;
            case 18 :
                block = std::string("IIR");   //Plane E
                break;
            case 19 :
                block = std::string("IIR");   //Plane D
                break;
            case 20 :
                block = std::string("IIR");   //Plane E
                break;
            case 21 :
                block = std::string("IIR");   //Plane D
                break;
            case 22 :
                block = std::string("IIR");   //Plane E
                break;
            case 23 :
                block = std::string("IIR");   //Plane F
                break;
            case 24 :
                block = std::string("IIA");   //Plane D Decommissioned from active service on 04 Nov 2011
                break;
            case 25 :
                block = std::string("IIF");   //Plane B
                break;
            case 26 :
                block = std::string("IIA");   //Plane F
                break;
            case 27 :
                block = std::string("IIA");   //Plane A
                break;
            case 28 :
                block = std::string("IIR");   //Plane B
                break;
            case 29 :
                block = std::string("IIR-M"); //Plane D
                break;
            case 30 :
                block = std::string("IIA");   //Plane B
                break;
            case 31 :
                block = std::string("IIR-M"); //Plane A
                break;
            case 32 :
                block = std::string("IIA");   //Plane E
                break;
            default :
                block = std::string("Unknown");
            }
        }


    if (system_.compare("Glonass") == 0)
        {
            switch ( PRN_ )
            {
            // info from http://www.sdcm.ru/smglo/grupglo?version=eng&site=extern

            case 1 :
                block = std::string("1");   //Plane 1
                break;
            case 2 :
                block = std::string("-4");  //Plane 1
                break;
            case 3 :
                block = std::string("5");   //Plane 1
                break;
            case 4 :
                block = std::string("6");   //Plane 1
                break;
            case 5 :
                block = std::string("1");   //Plane 1
                break;
            case 6 :
                block = std::string("-4");  //Plane 1
                break;
            case 7 :
                block = std::string("5");   //Plane 1
                break;
            case 8 :
                block = std::string("6");   //Plane 1
                break;
            case 9 :
                block = std::string("-2");  //Plane 2
                break;
            case 10 :
                block = std::string("-7");  //Plane 2
                break;
            case 11 :
                block = std::string("0");   //Plane 2
                break;
            case 12 :
                block = std::string("-1");  //Plane 2
                break;
            case 13 :
                block = std::string("-2");  //Plane 2
                break;
            case 14 :
                block = std::string("-7");  //Plane 2
                break;
            case 15 :
                block = std::string("0");   //Plane 2
                break;
            case 16 :
                block = std::string("-1");  //Plane 2
                break;
            case 17 :
                block = std::string("4");   //Plane 3
                break;
            case 18 :
                block = std::string("-3");  //Plane 3
                break;
            case 19 :
                block = std::string("3");   //Plane 3
                break;
            case 20 :
                block = std::string("2");   //Plane 3
                break;
            case 21 :
                block = std::string("4");   //Plane 3
                break;
            case 22 :
                block = std::string("-3");  //Plane 3
                break;
            case 23 :
                block = std::string("3");   //Plane 3
                break;
            case 24 :
                block = std::string("2");   //Plane 3
                break;
            default :
                block = std::string("Unknown");
            }
        }
    if (system_.compare("SBAS") == 0)
            {
                switch ( PRN_ )
                {
                case 122 :
                    block = std::string("WAAS");  // WAAS Inmarsat 3F4 (AOR-W)
                    break;
                case 134 :
                    block = std::string("WAAS");  // WAAS Inmarsat 3F3 (POR)
                    break;
                case 120 :
                    block = std::string("EGNOS"); // EGNOS AOR-E Broadcast satellite http://www.egnos-pro.esa.int/index.html
                case 124 :
                    block = std::string("EGNOS"); // EGNOS ESA ARTEMIS used for EGNOS Operations
                    break;
                case 126 :
                    block = std::string("EGNOS"); // EGNOS IOR-W  currently used by Industry to perform various tests on the system.
                    break;
                default:
                    block = std::string("Unknown");
                }
            }
    if (system_.compare("Galileo") == 0)
        {
            switch ( PRN_ )
            {
            case 11 :
                block = std::string("IOV"); // Launched from French Guiana at 10:30 GMT on October 21, 2011
                break;
            default:
                block = std::string("Unknown");
            }
        }
}




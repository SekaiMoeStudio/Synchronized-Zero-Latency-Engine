
#ifndef SZENEXT_HPP
#define SZENEXT_HPP

#include "../tool/readconfig.hpp"
#include "../tool/mods.hpp"
#include "utils.hpp"
#include "unistd.h"
#include <iostream>
#include <string>
#include <sys/inotify.h>
#include <thread>
using namespace std;
class SZENEXT {
public:
    string Mods,Mtemp;
    Utils utils;
    Rconfig config;
    MODS mods;
    int OC;
    const char * configfile = "/storage/emulated/0/Android/SZE_NEXT/config.txt";

    int fd = inotify_init();
    int wd = inotify_add_watch(fd, configfile, IN_MODIFY);
    char buff[1024];


    void Readx(){
        config.ReadConfig();
        config.ReadSetConfig();
        while (1) {
            int len = read(fd, buff, sizeof(buff));
            for (char * i = buff; i < buff + len;) {
                auto *eve= reinterpret_cast<inotify_event*>(i);
                if (eve -> mask & IN_MODIFY) {
                    ifstream file = mods.GETC();
                    string modss;
                    while (getline(file,modss))
                    {
                        Mods = std::move(modss);
                    }
                    PDMODS();
                    SetGover();
                }
                i += sizeof(inotify_event) + eve->len;
            }
        }
    }

    string GETFreqPath(string* policy){
        return "/sys/devices/system/cpu/cpufreq/policy" + *policy + "/scaling_max_freq";
    }

    string GETGoverPath(string* policy){
        return "/sys/devices/system/cpu/cpufreq/policy" + *policy + "/scaling_governor";
    }

    string GETGovernorPath(string* policy, string* gover, string* path){
        return "/sys/devices/system/cpu/cpufreq/policy" + *policy + "/" + *gover + "/" + *path;
    }


    void PDMODS(){
            if (Mods == "powersave")
            {
                    utils.Writer(GETFreqPath(config.MINpolicy),*config.POW_MINCORE);
                    utils.Writer(GETFreqPath(config.MIDpolicy),*config.POW_MIDCORE);
                    utils.Writer(GETGoverPath(config.MINpolicy),*config.POW_MIN_Gover);
                    utils.Writer(GETGoverPath(config.MIDpolicy),*config.POW_MID_Gover);
                    
                    if (*config.policynum == 3) {
                        utils.Writer(GETFreqPath(config.BIGpolicy),*config.POW_BIGCORE);
                        utils.Writer(GETGoverPath(config.BIGpolicy),*config.POW_BIG_Gover);
                    }
                    else if (*config.policynum == 4) {
                        utils.Writer(GETFreqPath(config.BIGpolicy),*config.POW_BIGCORE);
                        utils.Writer(GETFreqPath( config.EBIGpolicy),*config.POW_EBIGCORE);
                        utils.Writer(GETGoverPath(config.BIGpolicy),*config.POW_BIG_Gover);
                        utils.Writer(GETGoverPath(config.EBIGpolicy),*config.POW_EBIG_Gover);

                    }
                if (Mods != Mtemp)
                { 
                    utils.log(("INFO:"+Mods+"模式启动").c_str());
                    Mtemp = Mods;
                }
            
            }

            else if(Mods == "balance")
            {

                    utils.Writer(GETFreqPath(config.MINpolicy),*config.BAN_MINCORE);
                    utils.Writer(GETFreqPath(config.MIDpolicy),*config.BAN_MIDCORE);
                    utils.Writer(GETGoverPath(config.MINpolicy),*config.BAN_MIN_Gover);
                    utils.Writer(GETGoverPath(config.MIDpolicy),*config.BAN_MID_Gover);
                    if (*config.policynum == 3) {
                        utils.Writer(GETFreqPath(config.BIGpolicy),*config.BAN_BIGCORE);
                        utils.Writer(GETGoverPath(config.BIGpolicy),*config.BAN_BIG_Gover);
                    }
                    else if (*config.policynum == 4) {
                        utils.Writer(GETFreqPath(config.BIGpolicy),*config.BAN_BIGCORE);
                        utils.Writer(GETFreqPath(config.EBIGpolicy),*config.BAN_EBIGCORE);
                        utils.Writer(GETGoverPath(config.BIGpolicy),*config.BAN_BIG_Gover);
                        utils.Writer(GETGoverPath(config.EBIGpolicy),*config.BAN_EBIG_Gover);
                    }

                if (Mods != Mtemp)
                {
                    utils.log(("INFO:"+Mods+"模式启动").c_str());
                    Mtemp = Mods;
                }

            }

            else if (Mods == "performance")
            {
                    utils.Writer(GETFreqPath(config.MINpolicy),*config.PER_MINCORE);
                    utils.Writer(GETFreqPath(config.MIDpolicy),*config.PER_MIDCORE);
                    utils.Writer(GETGoverPath(config.MINpolicy),*config.PER_MIN_Gover);
                    utils.Writer(GETGoverPath(config.MIDpolicy),*config.PER_MID_Gover);
                    if (*config.policynum == 3) {
                        utils.Writer(GETFreqPath(config.BIGpolicy),*config.PER_BIGCORE);
                        utils.Writer(GETGoverPath(config.BIGpolicy),*config.PER_BIG_Gover);
                    }
                    else if (*config.policynum == 4) {
                        utils.Writer(GETFreqPath(config.BIGpolicy),*config.PER_BIGCORE);
                        utils.Writer(GETFreqPath(config.EBIGpolicy),*config.PER_EBIGCORE);
                        utils.Writer(GETGoverPath(config.BIGpolicy),*config.PER_BIG_Gover);
                        utils.Writer(GETGoverPath(config.EBIGpolicy),*config.PER_EBIG_Gover);
                    }

                if (Mods != Mtemp)
                {
                    utils.log(("INFO:"+Mods+"模式启动").c_str());
                    Mtemp = Mods;
                }
            }

            else if (Mods == "fast")
            {
                    utils.Writer(GETFreqPath(config.MINpolicy),*config.FAS_MINCORE);
                    utils.Writer(GETFreqPath(config.MIDpolicy),*config.FAS_MIDCORE);
                    utils.Writer(GETGoverPath(config.MINpolicy),*config.FAS_MIN_Gover);
                    utils.Writer(GETGoverPath(config.MIDpolicy),*config.FAS_MID_Gover);
                    if (*config.policynum == 3) {
                        utils.Writer(GETFreqPath(config.BIGpolicy),*config.FAS_BIGCORE);
                        utils.Writer(GETGoverPath(config.BIGpolicy),*config.FAS_BIG_Gover);
                    }
                    else if (*config.policynum == 4) {
                        utils.Writer(GETFreqPath(config.BIGpolicy),*config.FAS_BIGCORE);
                        utils.Writer(GETFreqPath(config.EBIGpolicy),*config.FAS_EBIGCORE);
                        utils.Writer(GETGoverPath(config.BIGpolicy),*config.FAS_BIG_Gover);
                        utils.Writer(GETGoverPath(config.EBIGpolicy),*config.FAS_EBIG_Gover);
                    }

                if (Mods != Mtemp)
                {
                    utils.log(("INFO:"+Mods+"模式启动").c_str());
                    Mtemp = Mods;
                }
            }
    }


    void SetGover(){
        if (Mods == "powersave")
        {
            if (*config.Setnum == 1)
            {
                utils.Writer(GETGovernorPath(config.MINpolicy, config.POW_MIN_Gover, config.Setname1), *config.POW_SetG_MIN_N1);
                utils.Writer(GETGovernorPath(config.MIDpolicy, config.POW_MID_Gover, config.Setname1), *config.POW_SetG_MID_N1);
                if (*config.policynum == 3) {
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.POW_BIG_Gover, config.Setname1), *config.POW_SetG_BIG_N1);
                }
                else if (*config.policynum == 4) {
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.POW_BIG_Gover, config.Setname1), *config.POW_SetG_BIG_N1);
                    utils.Writer(GETGovernorPath(config.EBIGpolicy, config.POW_EBIG_Gover, config.Setname1), *config.POW_SetG_EBIG_N1);
                }
            }

            else if (*config.Setnum == 2)
            {
                utils.Writer(GETGovernorPath(config.MINpolicy, config.POW_MIN_Gover, config.Setname1), *config.POW_SetG_MIN_N1);
                utils.Writer(GETGovernorPath(config.MINpolicy, config.POW_MIN_Gover, config.Setname2), *config.POW_SetG_MIN_N2);
                utils.Writer(GETGovernorPath(config.MIDpolicy, config.POW_MID_Gover, config.Setname1), *config.POW_SetG_MID_N1);
                utils.Writer(GETGovernorPath(config.MIDpolicy, config.POW_MID_Gover, config.Setname2), *config.POW_SetG_MID_N2);
                if (*config.policynum == 3) {
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.POW_BIG_Gover, config.Setname1), *config.POW_SetG_BIG_N1);
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.POW_BIG_Gover, config.Setname2), *config.POW_SetG_BIG_N2);
                }
                else if (*config.policynum == 4) {
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.POW_BIG_Gover, config.Setname1), *config.POW_SetG_BIG_N1);
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.POW_BIG_Gover, config.Setname2), *config.POW_SetG_BIG_N2);
                    utils.Writer(GETGovernorPath(config.EBIGpolicy, config.POW_EBIG_Gover, config.Setname1), *config.POW_SetG_EBIG_N1);
                    utils.Writer(GETGovernorPath(config.EBIGpolicy, config.POW_EBIG_Gover, config.Setname2), *config.POW_SetG_EBIG_N2);
                }
            }
            else if(*config.Setnum == 3)
            {
                utils.Writer(GETGovernorPath(config.MINpolicy, config.POW_MIN_Gover, config.Setname1), *config.POW_SetG_MIN_N1);
                utils.Writer(GETGovernorPath(config.MINpolicy, config.POW_MIN_Gover, config.Setname2), *config.POW_SetG_MIN_N2);
                utils.Writer(GETGovernorPath(config.MINpolicy, config.POW_MIN_Gover, config.Setname3), *config.POW_SetG_MIN_N3);
                utils.Writer(GETGovernorPath(config.MIDpolicy, config.POW_MID_Gover, config.Setname1), *config.POW_SetG_MID_N1);
                utils.Writer(GETGovernorPath(config.MIDpolicy, config.POW_MID_Gover, config.Setname2), *config.POW_SetG_MID_N2);
                utils.Writer(GETGovernorPath(config.MIDpolicy, config.POW_MID_Gover, config.Setname3), *config.POW_SetG_MID_N3);
                if (*config.policynum == 3) {
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.POW_BIG_Gover, config.Setname1), *config.POW_SetG_BIG_N1);
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.POW_BIG_Gover, config.Setname2), *config.POW_SetG_BIG_N2);
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.POW_BIG_Gover, config.Setname3), *config.POW_SetG_BIG_N3);
                }
                else if (*config.policynum == 4) {
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.POW_BIG_Gover, config.Setname1), *config.POW_SetG_BIG_N1);
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.POW_BIG_Gover, config.Setname2), *config.POW_SetG_BIG_N2);
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.POW_BIG_Gover, config.Setname3), *config.POW_SetG_BIG_N3);
                    utils.Writer(GETGovernorPath(config.EBIGpolicy, config.POW_EBIG_Gover, config.Setname1), *config.POW_SetG_EBIG_N1);
                    utils.Writer(GETGovernorPath(config.EBIGpolicy, config.POW_EBIG_Gover, config.Setname2), *config.POW_SetG_EBIG_N2);
                    utils.Writer(GETGovernorPath(config.EBIGpolicy, config.POW_EBIG_Gover, config.Setname3), *config.POW_SetG_EBIG_N3);
                }

            }

        }
        else if (Mods == "balance")
        {
            if (*config.Setnum == 1)
            {
                utils.Writer(GETGovernorPath(config.MINpolicy, config.BAN_MIN_Gover, config.Setname1), *config.BAN_SetG_MIN_N1);
                utils.Writer(GETGovernorPath(config.MIDpolicy, config.BAN_MID_Gover, config.Setname1), *config.BAN_SetG_MID_N1);
                if (*config.policynum == 3) {
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.BAN_BIG_Gover, config.Setname1), *config.BAN_SetG_BIG_N1);
                }
                else if (*config.policynum == 4) {
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.BAN_BIG_Gover, config.Setname1), *config.BAN_SetG_BIG_N1);
                    utils.Writer(GETGovernorPath(config.EBIGpolicy, config.BAN_EBIG_Gover, config.Setname1), *config.BAN_SetG_EBIG_N1);
                }
            }

            else if (*config.Setnum == 2)
            {
                utils.Writer(GETGovernorPath(config.MINpolicy, config.BAN_MIN_Gover, config.Setname1), *config.BAN_SetG_MIN_N1);
                utils.Writer(GETGovernorPath(config.MINpolicy, config.BAN_MIN_Gover, config.Setname2), *config.BAN_SetG_MIN_N2);
                utils.Writer(GETGovernorPath(config.MIDpolicy, config.BAN_MID_Gover, config.Setname1), *config.BAN_SetG_MID_N1);
                utils.Writer(GETGovernorPath(config.MIDpolicy, config.BAN_MID_Gover, config.Setname2), *config.BAN_SetG_MID_N2);
                if (*config.policynum == 3) {
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.BAN_BIG_Gover, config.Setname1), *config.BAN_SetG_BIG_N1);
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.BAN_BIG_Gover, config.Setname2), *config.BAN_SetG_BIG_N2);
                }
                else if (*config.policynum == 4) {
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.BAN_BIG_Gover, config.Setname1), *config.BAN_SetG_BIG_N1);
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.BAN_BIG_Gover, config.Setname2), *config.BAN_SetG_BIG_N2);
                    utils.Writer(GETGovernorPath(config.EBIGpolicy, config.BAN_EBIG_Gover, config.Setname1), *config.BAN_SetG_EBIG_N1);
                    utils.Writer(GETGovernorPath(config.EBIGpolicy, config.BAN_EBIG_Gover, config.Setname2), *config.BAN_SetG_EBIG_N2);
                }
            }
            else if (*config.Setnum == 3)
            {
                utils.Writer(GETGovernorPath(config.MINpolicy, config.BAN_MIN_Gover, config.Setname1), *config.BAN_SetG_MIN_N1);
                utils.Writer(GETGovernorPath(config.MINpolicy, config.BAN_MIN_Gover, config.Setname2), *config.BAN_SetG_MIN_N2);
                utils.Writer(GETGovernorPath(config.MINpolicy, config.BAN_MIN_Gover, config.Setname3), *config.BAN_SetG_MIN_N3);
                utils.Writer(GETGovernorPath(config.MIDpolicy, config.BAN_MID_Gover, config.Setname1), *config.BAN_SetG_MID_N1);
                utils.Writer(GETGovernorPath(config.MIDpolicy, config.BAN_MID_Gover, config.Setname2), *config.BAN_SetG_MID_N2);
                utils.Writer(GETGovernorPath(config.MIDpolicy, config.BAN_MID_Gover, config.Setname3), *config.BAN_SetG_MID_N3);
                if (*config.policynum == 3) {
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.BAN_BIG_Gover, config.Setname1), *config.BAN_SetG_BIG_N1);
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.BAN_BIG_Gover, config.Setname2), *config.BAN_SetG_BIG_N2);
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.BAN_BIG_Gover, config.Setname3), *config.BAN_SetG_BIG_N3);
                }
                else if (*config.policynum == 4) {
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.BAN_BIG_Gover, config.Setname1), *config.BAN_SetG_BIG_N1);
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.BAN_BIG_Gover, config.Setname2), *config.BAN_SetG_BIG_N2);
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.BAN_BIG_Gover, config.Setname3), *config.BAN_SetG_BIG_N3);
                    utils.Writer(GETGovernorPath(config.EBIGpolicy, config.BAN_EBIG_Gover, config.Setname1), *config.BAN_SetG_EBIG_N1);
                    utils.Writer(GETGovernorPath(config.EBIGpolicy, config.BAN_EBIG_Gover, config.Setname2), *config.BAN_SetG_EBIG_N2);
                    utils.Writer(GETGovernorPath(config.EBIGpolicy, config.BAN_EBIG_Gover, config.Setname3), *config.BAN_SetG_EBIG_N3);
                }
            }
        }

        else if (Mods == "performance")
        {
            if (*config.Setnum == 1)
            {
                utils.Writer(GETGovernorPath(config.MINpolicy, config.PER_MIN_Gover, config.Setname1), *config.PER_SetG_MIN_N1);
                utils.Writer(GETGovernorPath(config.MIDpolicy, config.PER_MID_Gover, config.Setname1), *config.PER_SetG_MID_N1);
                if (*config.policynum == 3) {
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.PER_BIG_Gover, config.Setname1), *config.PER_SetG_BIG_N1);
                }
                else if (*config.policynum == 4) {
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.PER_BIG_Gover, config.Setname1), *config.PER_SetG_BIG_N1);
                    utils.Writer(GETGovernorPath(config.EBIGpolicy, config.PER_EBIG_Gover, config.Setname1), *config.PER_SetG_EBIG_N1);
                }
            }

            else if (*config.Setnum == 2)
            {
                utils.Writer(GETGovernorPath(config.MINpolicy, config.PER_MIN_Gover, config.Setname1), *config.PER_SetG_MIN_N1);
                utils.Writer(GETGovernorPath(config.MINpolicy, config.PER_MIN_Gover, config.Setname2), *config.PER_SetG_MIN_N2);
                utils.Writer(GETGovernorPath(config.MIDpolicy, config.PER_MID_Gover, config.Setname1), *config.PER_SetG_MID_N1);
                utils.Writer(GETGovernorPath(config.MIDpolicy, config.PER_MID_Gover, config.Setname2), *config.PER_SetG_MID_N2);
                if (*config.policynum == 3) {
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.PER_BIG_Gover, config.Setname1), *config.PER_SetG_BIG_N1);
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.PER_BIG_Gover, config.Setname2), *config.PER_SetG_BIG_N2);
                }
                else if (*config.policynum == 4) {
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.PER_BIG_Gover, config.Setname1), *config.PER_SetG_BIG_N1);
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.PER_BIG_Gover, config.Setname2), *config.PER_SetG_BIG_N2);
                    utils.Writer(GETGovernorPath(config.EBIGpolicy, config.PER_EBIG_Gover, config.Setname1), *config.PER_SetG_EBIG_N1);
                    utils.Writer(GETGovernorPath(config.EBIGpolicy, config.PER_EBIG_Gover, config.Setname2), *config.PER_SetG_EBIG_N2);
                }
            }
            else if (*config.Setnum == 3)
            {
                utils.Writer(GETGovernorPath(config.MINpolicy, config.PER_MIN_Gover, config.Setname1), *config.PER_SetG_MIN_N1);
                utils.Writer(GETGovernorPath(config.MINpolicy, config.PER_MIN_Gover, config.Setname2), *config.PER_SetG_MIN_N2);
                utils.Writer(GETGovernorPath(config.MINpolicy, config.PER_MIN_Gover, config.Setname3), *config.PER_SetG_MIN_N3);
                utils.Writer(GETGovernorPath(config.MIDpolicy, config.PER_MID_Gover, config.Setname1), *config.PER_SetG_MID_N1);
                utils.Writer(GETGovernorPath(config.MIDpolicy, config.PER_MID_Gover, config.Setname2), *config.PER_SetG_MID_N2);
                utils.Writer(GETGovernorPath(config.MIDpolicy, config.PER_MID_Gover, config.Setname3), *config.PER_SetG_MID_N3);
                if (*config.policynum == 3) {
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.PER_BIG_Gover, config.Setname1), *config.PER_SetG_BIG_N1);
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.PER_BIG_Gover, config.Setname2), *config.PER_SetG_BIG_N2);
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.PER_BIG_Gover, config.Setname3), *config.PER_SetG_BIG_N3);
                }
                else if (*config.policynum == 4) {
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.PER_BIG_Gover, config.Setname1), *config.PER_SetG_BIG_N1);
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.PER_BIG_Gover, config.Setname2), *config.PER_SetG_BIG_N2);
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.PER_BIG_Gover, config.Setname3), *config.PER_SetG_BIG_N3);
                    utils.Writer(GETGovernorPath(config.EBIGpolicy, config.PER_EBIG_Gover, config.Setname1), *config.PER_SetG_EBIG_N1);
                    utils.Writer(GETGovernorPath(config.EBIGpolicy, config.PER_EBIG_Gover, config.Setname2), *config.PER_SetG_EBIG_N2);
                    utils.Writer(GETGovernorPath(config.EBIGpolicy, config.PER_EBIG_Gover, config.Setname3), *config.PER_SetG_EBIG_N3);
                }
            
            }
        }

        else if (Mods == "fast")
        {
            if (*config.Setnum == 1)
            {
                utils.Writer(GETGovernorPath(config.MINpolicy, config.FAS_MIN_Gover, config.Setname1), *config.FAS_SetG_MIN_N1);
                utils.Writer(GETGovernorPath(config.MIDpolicy, config.FAS_MID_Gover, config.Setname1), *config.FAS_SetG_MID_N1);
                if (*config.policynum == 3) {
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.FAS_BIG_Gover, config.Setname1), *config.FAS_SetG_BIG_N1);
                }
                else if (*config.policynum == 4) {
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.FAS_BIG_Gover, config.Setname1), *config.FAS_SetG_BIG_N1);
                    utils.Writer(GETGovernorPath(config.EBIGpolicy, config.FAS_EBIG_Gover, config.Setname1), *config.FAS_SetG_EBIG_N1);
                }
            }

            else if (*config.Setnum == 2)
            {
                utils.Writer(GETGovernorPath(config.MINpolicy, config.FAS_MIN_Gover, config.Setname1), *config.FAS_SetG_MIN_N1);
                utils.Writer(GETGovernorPath(config.MINpolicy, config.FAS_MIN_Gover, config.Setname2), *config.FAS_SetG_MIN_N2);
                utils.Writer(GETGovernorPath(config.MIDpolicy, config.FAS_MID_Gover, config.Setname1), *config.FAS_SetG_MID_N1);
                utils.Writer(GETGovernorPath(config.MIDpolicy, config.FAS_MID_Gover, config.Setname2), *config.FAS_SetG_MID_N2);
                if (*config.policynum == 3) {
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.FAS_BIG_Gover, config.Setname1), *config.FAS_SetG_BIG_N1);
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.FAS_BIG_Gover, config.Setname2), *config.FAS_SetG_BIG_N2);
                }
                else if (*config.policynum == 4) {
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.FAS_BIG_Gover, config.Setname1), *config.FAS_SetG_BIG_N1);
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.FAS_BIG_Gover, config.Setname2), *config.FAS_SetG_BIG_N2);
                    utils.Writer(GETGovernorPath(config.EBIGpolicy, config.FAS_EBIG_Gover, config.Setname1), *config.FAS_SetG_EBIG_N1);
                    utils.Writer(GETGovernorPath(config.EBIGpolicy, config.FAS_EBIG_Gover, config.Setname2), *config.FAS_SetG_EBIG_N2);
                }
            }

            else if (*config.Setnum == 3)
            {
                utils.Writer(GETGovernorPath(config.MINpolicy, config.FAS_MIN_Gover, config.Setname1), *config.FAS_SetG_MIN_N1);
                utils.Writer(GETGovernorPath(config.MINpolicy, config.FAS_MIN_Gover, config.Setname2), *config.FAS_SetG_MIN_N2);
                utils.Writer(GETGovernorPath(config.MINpolicy, config.FAS_MIN_Gover, config.Setname3), *config.FAS_SetG_MIN_N3);
                utils.Writer(GETGovernorPath(config.MIDpolicy, config.FAS_MID_Gover, config.Setname1), *config.FAS_SetG_MID_N1);
                utils.Writer(GETGovernorPath(config.MIDpolicy, config.FAS_MID_Gover, config.Setname2), *config.FAS_SetG_MID_N2);
                utils.Writer(GETGovernorPath(config.MIDpolicy, config.FAS_MID_Gover, config.Setname3), *config.FAS_SetG_MID_N3);
                if (*config.policynum == 3) {
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.FAS_BIG_Gover, config.Setname1), *config.FAS_SetG_BIG_N1);
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.FAS_BIG_Gover, config.Setname2), *config.FAS_SetG_BIG_N2);
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.FAS_BIG_Gover, config.Setname3), *config.FAS_SetG_BIG_N3);
                }
                else if (*config.policynum == 4) {
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.FAS_BIG_Gover, config.Setname1), *config.FAS_SetG_BIG_N1);
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.FAS_BIG_Gover, config.Setname2), *config.FAS_SetG_BIG_N2);
                    utils.Writer(GETGovernorPath(config.BIGpolicy, config.FAS_BIG_Gover, config.Setname3), *config.FAS_SetG_BIG_N3);
                    utils.Writer(GETGovernorPath(config.EBIGpolicy, config.FAS_EBIG_Gover, config.Setname1), *config.FAS_SetG_EBIG_N1);
                    utils.Writer(GETGovernorPath(config.EBIGpolicy, config.FAS_EBIG_Gover, config.Setname2), *config.FAS_SetG_EBIG_N2);
                    utils.Writer(GETGovernorPath(config.EBIGpolicy, config.FAS_EBIG_Gover, config.Setname3), *config.FAS_SetG_EBIG_N3);
                }
            }
        
        }
    }


    void COC (){
        while (1)
        {
            auto c1 = utils.readCpuStats();
            sleep(2);
            auto c2 = utils.readCpuStats();
            OC = utils.calculateTotalCpuLoad(c1,c2);
        }
    }


    void init(){
        config.Readname();
        utils.log(("******调度配置：" + config.name).c_str());
        utils.log(("******配置版本：" + config.lv).c_str());
        utils.log(("******配置作者：" + config.Out).c_str());


    }

};

#endif

//
//  CommonLayerSet.m
//  GameBox
//
//  Created by  on 12-5-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "FileConfigure.h"

FileConfigure::FileConfigure(){
}

FileConfigure::~FileConfigure()
{
}

void FileConfigure::ReadOption()
{
	const char *fn = "g_config.txt";
	const char *path = GetDocPath(fn, NULL);
    printf("config file path is %s\n", path);
	FILE *fp;
	//printf("g_config hashmap size=%d\n", g_config.size());
    if(g_config.size()==0)
    {
        printf("Init g_config hashmap\n");
        //初始化hash_map
        char *tmp;
        tmp=(char *)malloc(G_CONFIG_VALUE_LENGTH);
        sprintf(tmp, "%d", 1);
        g_config["sound"]=tmp;
        //printf("SADDRESS=%d\n", g_config["sound"]);
        
        tmp=(char *)malloc(G_CONFIG_VALUE_LENGTH);
        sprintf(tmp, "%d", 0);
        g_config["shock"]=tmp;
        
        tmp=(char *)malloc(G_CONFIG_VALUE_LENGTH);
        sprintf(tmp, "%d", 1);
        g_config["autosit"]=tmp;
        
        //登录类型
        tmp=(char *)malloc(G_CONFIG_VALUE_LENGTH);
        sprintf(tmp, "&&^^_null");
        g_config["login_type"]=tmp;
        
        //新浪token
        tmp=(char *)malloc(G_CONFIG_VALUE_LENGTH);
        sprintf(tmp, "&&^^_null");
        g_config["sina_uid"]=tmp;
        //新浪用户uid
        tmp=(char *)malloc(G_CONFIG_VALUE_LENGTH);
        sprintf(tmp, "&&^^_null");
        g_config["sina_accesstoken"]=tmp;
        
        //QQ登录openid
        tmp=(char *)malloc(G_CONFIG_VALUE_LENGTH);
        sprintf(tmp, "&&^^_null");
        g_config["qq_openid"]=tmp;
        //QQ登录token
        tmp=(char *)malloc(G_CONFIG_VALUE_LENGTH);
        sprintf(tmp, "&&^^_null");
        g_config["qq_accesstoken"]=tmp;
        
        //人人登录uid
        tmp=(char *)malloc(G_CONFIG_VALUE_LENGTH);
        sprintf(tmp, "&&^^_null");
        g_config["renren_uid"]=tmp;
        //人人登录token
        tmp=(char *)malloc(G_CONFIG_VALUE_LENGTH);
        sprintf(tmp, "&&^^_null");
        g_config["renren_accesstoken"]=tmp;
        //人人登录session_key
        tmp=(char *)malloc(G_CONFIG_VALUE_LENGTH);
        sprintf(tmp, "&&^^_null");
        g_config["renren_sessionKey"]=tmp;
        
        //游客昵称
        tmp=(char *)malloc(G_CONFIG_VALUE_LENGTH);
        sprintf(tmp, "&&^^_null");
        g_config["guest_nick"]=tmp;
    }
    
	if((fp=fopen(path, "r"))==NULL)
	{        
        printf("the g_config file is null\n");
	}
	else
	{
        while (1) 
        {
            char confname[50];
            char confvalue[G_CONFIG_VALUE_LENGTH];
            int ret=fscanf(fp, "%s\t%[^\n]", confname, confvalue);
            if (ret!=2) break;
            hash_map<const char *, char *>::iterator itr;
            for(itr=g_config.begin(); itr!=g_config.end(); itr++)
            {
                if (strcmp(confname, itr->first)==0)
                    sprintf(itr->second, "%s", confvalue);
            }

        }
		fclose(fp);
	}
}

void FileConfigure::WriteOption()
{
	FILE *fp;
	
	const char *fn = "g_config.txt";
	const char *path = GetDocPath(fn, NULL);
	
	if((fp=fopen(path,"rb+"))==NULL)
	{
		if((fp=fopen(path, "wb+"))==NULL)
			return;
    }
    
    printf("------------------------------\n");
    hash_map<const char *, char *>::iterator itr;
    for(itr=g_config.begin(); itr!=g_config.end(); itr++)
    {
        fprintf(fp, "%s\t%s\n", itr->first, itr->second);
        printf("%s: %s\t|\n", itr->first, itr->second);
    }
    printf("------------------------------\n");
	fclose(fp);
}




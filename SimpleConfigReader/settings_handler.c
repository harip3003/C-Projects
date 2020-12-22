/**
 * @file settings_handler.c Implementation file for the settings handler
 * @author : Harikrishnan P
 * @Date : 22 December 2020
 * */

#include "settings_handler.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SETTINGS_NAME_WIDTH 20
#define MAX_SETTINGS_VAL_WIDTH  20
#define MAX_LINE_WIDTH          40
#define SETTINGS_DELIMITER      "="

struct SettingsNameValuePair{
    char name[MAX_SETTINGS_NAME_WIDTH];
    char value[MAX_SETTINGS_VAL_WIDTH];
};

struct SettingsStruct{
    struct SettingsNameValuePair* settings;
    int numberOfSettings;
};

static bool openSettingsFile(char *, FILE **);
static void copySettingsNameValuePair(struct SettingsNameValuePair *, char *, char *);
static int  getNumberOfSettings(FILE* fp);

SettingsHandle_t getSettingsFileHandler(int numberOfSettings)
{
    SettingsHandle_t handle  = malloc(sizeof(SettingsHandle_t));

    if(handle == NULL)
        return NULL;
    
    handle->settings         = calloc(numberOfSettings,
                                      sizeof(struct SettingsNameValuePair));

    handle->numberOfSettings = numberOfSettings;
    return handle;
}

SettingsHandle_t loadSettingsFromFile(char* fileName)
{
    FILE *fp;
    SettingsHandle_t handle;
    
    if(!openSettingsFile(fileName, &fp))
        return NULL;

    handle = getSettingsFileHandler(getNumberOfSettings(fp));
    
    char line[MAX_LINE_WIDTH];
    int index = 0;
    while(fgets(line, MAX_LINE_WIDTH, fp) && index < handle->numberOfSettings)
    {
        //Removing the new line character
        line[strcspn(line, "\n")] = 0; 

        char *name, *value;
        if( name  = strtok(line, SETTINGS_DELIMITER))
            value = strtok(NULL, SETTINGS_DELIMITER);

        copySettingsNameValuePair(&handle->settings[index], name, value);

        index++;
    }

    return handle;
}

char* getSettingsValue(SettingsHandle_t handle, char *settingName)
{
    char *settingValue = NULL;

    for(int index = 0; index < handle->numberOfSettings; index++)
    {
        if(!strcmp(handle->settings[index].name, settingName))
        {
            settingValue = handle->settings[index].value;
            break;
        }
    }
    return settingValue;
}

bool openSettingsFile(char *fileName, FILE **fp)
{
    *fp = fopen(fileName, "r");
    if(*fp == NULL)
        return false;
    
    return true;
}

int getNumberOfSettings(FILE *fp)
{
    char line[MAX_LINE_WIDTH];
    int numberOfSettings;
    fgets(line, MAX_LINE_WIDTH, fp);

    line[strcspn(line, "\n")];
    sscanf(line, "%d", &numberOfSettings);

    return numberOfSettings;
}

void copySettingsNameValuePair(struct SettingsNameValuePair* setting, char *settingName, char *settingValue)
{
    if(settingName == NULL || settingValue == NULL)
    {
        return;
    }
    strcpy(setting->name,  settingName);
    strcpy(setting->value, settingValue);
}

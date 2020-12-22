#include <stdio.h>
#include "settings_handler.h"

int main()
{
    // Reading from demo_settings_file in the same path
    SettingsHandle_t setting = loadSettingsFromFile("demo_settings_file");

    if(setting == NULL)
    {	
	printf("Error in reading from file !\n");
	return -1;
    }

    printf("Port : %s\n", getSettingsValue(setting, "port"));
    printf("Parity: %s\n", getSettingsValue(setting, "parity"));
}

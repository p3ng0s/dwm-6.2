/*
** p4p1: http://p4p1.github.io/
** Created on: dim. 31 mai 2020 07:50:09  CEST
** status.c
** File description:
** <..>
*/

#include <time.h>
#include <dirent.h>

#define TESTING_COLORS (" \x06[ok]\x01 \x05[custom]\x01 \x04[urgent]\x01 \x03[warning]\x01 \x02[selected]\x01 [normal]\0")

static char *
set_ac(void)
{
	char tmp;
	char *str = malloc(sizeof(char) * BUFSIZ);
	FILE *fp = fopen("/sys/class/power_supply/AC/online", "r");

	if (str == NULL || fp == NULL)
		return (NULL);
	memset(str, 0, BUFSIZ);
	if (fgets(&tmp, 1, (FILE *)fp) == NULL)
		return (NULL);
	if (tmp == '1') {
		strcpy(str, "\x02ch -- \x01");
	}
	return (str);
}

static char *
set_bat(char *bat)
{
	char tmp[5] = { 0, 0, 0, 0, 0};
	char *str = malloc(sizeof(char) * BUFSIZ);
	char *bat_name = malloc(sizeof(char) * (32 + strlen(bat)));
	FILE *fp = NULL;

	sprintf(bat_name, "/sys/class/power_supply/%s/capacity", bat);
	fp = fopen(bat_name, "r");
	if (str == NULL || fp == NULL)
		return (NULL);
	memset(str, 0, BUFSIZ);
	if (fgets(tmp, 3, (FILE *)fp) == NULL) {
		free(bat_name);
		return (NULL);
	}
	sprintf(str, "%s%%", tmp);
	free(bat_name);
	return (str);
}

static char *
status_get_battery(void)
{
	char *str = NULL;
	char *tmp = NULL;
	struct dirent *de;
	DIR *dr = opendir("/sys/class/power_supply/");

	if (dr == NULL)
		return (NULL);
	if ((str = malloc(sizeof(char) * BUFSIZ)) == NULL)
		return (NULL);
	memset(str, 0, BUFSIZ);
	strcat(str, "[");
	while ((de = readdir(dr)) != NULL) {
		if (de->d_name[0] == '.')
			continue;
		if (strcmp(de->d_name, "AC") == 0) {
			if ((tmp = set_ac()) == NULL)
				return (NULL);
			strcat(str, tmp);
			free(tmp);
		} else {
			if ((tmp = set_bat(de->d_name)) == NULL)
				return (NULL);
			strcat(str, tmp);
			free(tmp);
		}
	}
	strcat(str, "]");
	return (str);
}

static char *
status_get_time(void)
{
	char *str = malloc(sizeof(char) * BUFSIZ);
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	if (str == NULL)
		return (NULL);
	memset(str, 0, BUFSIZ);
	sprintf(str, "[%d/%02d/%02d %02d:%02d] ", tm.tm_year + 1900,
			tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min);
	return (str);
}

void
status(void)
{
	char *tmp = NULL;
	char *(*fp[])(void) = { &status_get_time, &status_get_battery, NULL };

	memset(stext, 0, 256);
	strcat(stext, " ");
	for (unsigned int i = 0; fp[i] && strlen(stext) < 256 ; i++) {
		tmp = fp[i]();
		if (tmp != NULL)
			strcat(stext, tmp);
		free(tmp);
	}
	strcpy(stext, TESTING_COLORS);
}

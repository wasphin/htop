#ifndef HEADER_Settings
#define HEADER_Settings
/*
htop - Settings.h
(C) 2004-2011 Hisham H. Muhammad
Released under the GNU GPLv2, see the COPYING file
in the source distribution for its full text.
*/

#include "config.h" // IWYU pragma: keep

#include <stdbool.h>
#include <stdint.h>

#include "Process.h"


#define DEFAULT_DELAY 15

typedef struct {
   int len;
   char** names;
   int* modes;
} MeterColumnSettings;

typedef struct Settings_ {
   char* filename;
   MeterColumnSettings columns[2];

   ProcessField* fields;
   uint32_t flags;
   int colorScheme;
   int delay;

   int direction;
   int treeDirection;
   ProcessField sortKey;
   ProcessField treeSortKey;

   bool countCPUsFromOne;
   bool detailedCPUTime;
   bool showCPUUsage;
   bool showCPUFrequency;
   #ifdef HAVE_SENSORS_SENSORS_H
   bool showCPUTemperature;
   bool degreeFahrenheit;
   #endif
   bool treeView;
   bool treeViewAlwaysByPID;
   bool showProgramPath;
   bool shadowOtherUsers;
   bool showThreadNames;
   bool hideKernelThreads;
   bool hideUserlandThreads;
   bool highlightBaseName;
   bool highlightMegabytes;
   bool highlightThreads;
   bool highlightChanges;
   int highlightDelaySecs;
   bool findCommInCmdline;
   bool stripExeFromCmdline;
   bool showMergedCommand;
   bool updateProcessNames;
   bool accountGuestInCPUMeter;
   bool headerMargin;
   bool enableMouse;
   int hideFunctionBar;  // 0 - off, 1 - on ESC until next input, 2 - permanently
   #ifdef HAVE_LIBHWLOC
   bool topologyAffinity;
   #endif

   bool changed;
} Settings;

#define Settings_cpuId(settings, cpu) ((settings)->countCPUsFromOne ? (cpu)+1 : (cpu))

static inline ProcessField Settings_getActiveSortKey(const Settings* this) {
   return (this->treeView)
          ? (this->treeViewAlwaysByPID ? PID : this->treeSortKey)
          : this->sortKey;
}

static inline int Settings_getActiveDirection(const Settings* this) {
   return this->treeView ? this->treeDirection : this->direction;
}

void Settings_delete(Settings* this);

bool Settings_write(Settings* this);

Settings* Settings_new(int initialCpuCount);

void Settings_invertSortOrder(Settings* this);

void Settings_setSortKey(Settings* this, ProcessField sortKey);

#endif

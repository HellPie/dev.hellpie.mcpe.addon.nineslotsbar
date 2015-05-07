#include <dlfcn.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <android/log.h>
#include <jni.h>
#include <string>

#include <substrate.h>
#include <dobby_public.h>
#include <dl_internal.h>

typedef struct {
	char filler[420];
	int numSlots;
} Gui;

static void (*hook_Gui_tick_orig)(Gui*);

void MSHookFunction(void *symbol, void *hook, void **real);

void hook_Gui_tick_mod(Gui* mGui) {
	mGui->numSlots = 9;
	hook_Gui_tick_orig(mGui);
}

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
	  
  	void *handle;
  	handle = dlopen("libminecraftpe.so", RTLD_LAZY);
  	soinfo2* weakhandle = (soinfo2*) dlopen("libminecraftpe.so", RTLD_LAZY);

	void* hook_Gui_tick = dlsym(handle, "_ZN3Gui4tickEv");
	MSHookFunction(hook_Gui_tick, (void*) &hook_Gui_tick_mod, (void**) &hook_Gui_tick_orig);
	
  	return JNI_VERSION_1_2;
}


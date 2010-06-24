#define TAG "android_media_FFMpegAVFormatContext"

#include <android/log.h>
#include "jniUtils.h"

#include "../libavformat/avformat.h"

struct fields_t
{
    jmethodID formatContext;
};
static struct fields_t fields;

jobject *newAVFormatContext(JNIEnv *env, AVFormatContext *fileContext) {
	jclass clazz = (*env)->FindClass(env, "android/media/ffmpeg/FFMpegAVFormatContext");
	jobject result = (*env)->NewObject(env, clazz, fields.formatContext);

	// set native pointer to java class for later use
	(*env)->SetIntField(env, result, (*env)->GetFieldID(env, clazz, "pointer", "I"), (jint)fileContext);

	(*env)->SetIntField(env, result, (*env)->GetFieldID(env, clazz,
			"nb_streams", "I"), fileContext->nb_streams);
	(*env)->SetIntField(env, result,
			(*env)->GetFieldID(env, clazz, "year", "I"), fileContext->year);
	(*env)->SetIntField(env, result, (*env)->GetFieldID(env, clazz, "track",
			"I"), fileContext->track);
	(*env)->SetIntField(env, result, (*env)->GetFieldID(env, clazz, "bit_rate",
			"I"), fileContext->bit_rate);
	(*env)->SetIntField(env, result, (*env)->GetFieldID(env, clazz, "mux_rate",
			"I"), fileContext->mux_rate);
	(*env)->SetIntField(env, result, (*env)->GetFieldID(env, clazz,
			"packet_size", "I"), fileContext->packet_size);
	(*env)->SetIntField(env, result, (*env)->GetFieldID(env, clazz, "preload",
			"I"), fileContext->preload);
	(*env)->SetIntField(env, result, (*env)->GetFieldID(env, clazz,
			"max_delay", "I"), fileContext->max_delay);
	(*env)->SetIntField(env, result, (*env)->GetFieldID(env, clazz,
			"loop_output", "I"), fileContext->loop_output);
	(*env)->SetIntField(env, result, (*env)->GetFieldID(env, clazz, "flags",
			"I"), fileContext->flags);
	(*env)->SetIntField(env, result, (*env)->GetFieldID(env, clazz,
			"loop_input", "I"), fileContext->loop_input);

	(*env)->SetLongField(env, result, (*env)->GetFieldID(env, clazz,
			"timestamp", "J"), fileContext->timestamp);
	(*env)->SetLongField(env, result, (*env)->GetFieldID(env, clazz,
			"start_time", "J"), fileContext->start_time);
	(*env)->SetLongField(env, result, (*env)->GetFieldID(env, clazz,
			"duration", "J"), fileContext->duration);
	(*env)->SetLongField(env, result, (*env)->GetFieldID(env, clazz,
			"file_size", "J"), fileContext->file_size);
	(*env)->SetObjectField(env, result, (*env)->GetFieldID(env, clazz,
			"filename", "Ljava/lang/String;"), (*env)->NewStringUTF(env,
			fileContext->filename));
	(*env)->SetObjectField(env, result, (*env)->GetFieldID(env, clazz, "title",
			"Ljava/lang/String;"),
			(*env)->NewStringUTF(env, fileContext->title));
	(*env)->SetObjectField(env, result, (*env)->GetFieldID(env, clazz,
			"author", "Ljava/lang/String;"), (*env)->NewStringUTF(env,
			fileContext->author));
	(*env)->SetObjectField(env, result, (*env)->GetFieldID(env, clazz,
			"copyright", "Ljava/lang/String;"), (*env)->NewStringUTF(env,
			fileContext->copyright));
	(*env)->SetObjectField(env, result, (*env)->GetFieldID(env, clazz,
			"comment", "Ljava/lang/String;"), (*env)->NewStringUTF(env,
			fileContext->comment));
	(*env)->SetObjectField(env, result, (*env)->GetFieldID(env, clazz, "album",
			"Ljava/lang/String;"),
			(*env)->NewStringUTF(env, fileContext->album));
	(*env)->SetObjectField(env, result, (*env)->GetFieldID(env, clazz, "genre",
			"Ljava/lang/String;"),
			(*env)->NewStringUTF(env, fileContext->genre));
	return result;
}

static void release(JNIEnv *env, jobject thiz, jint pointer) {
	AVFormatContext *fileContext = (AVFormatContext *) pointer;
	__android_log_print(ANDROID_LOG_INFO, TAG,  "releasing FFMpegAVFormatContext"),
	free(fileContext);
}

/*
 * JNI registration.
 */
static JNINativeMethod methods[] = {
	{ "nativeRelease", "(I)V", (void*) release }
};

int register_android_media_FFMpegAVFormatContext(JNIEnv *env) {
	jclass clazz = (*env)->FindClass(env, "android/media/ffmpeg/FFMpegAVFormatContext");
	fields.formatContext = (*env)->GetMethodID(env, clazz, "<init>", "()V");
	if (fields.formatContext == NULL) {
		jniThrowException(env,
	                      "java/lang/RuntimeException",
	                      "can't load clb_onReport callback");
	}

	return jniRegisterNativeMethods(env, "android/media/ffmpeg/FFMpegAVFormatContext", methods, sizeof(methods) / sizeof(methods[0]));
}
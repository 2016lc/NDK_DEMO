#include <jni.h>
#include <string>
#include <android/log.h>

#define LOG    "demo-jni" // 这个是自定义的LOG的标识
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...)  __android_log_print(ANDROID_LOG_FATAL,LOG,__VA_ARGS__) // 定义LOGF类型

jmethodID mid;

extern "C"
JNIEXPORT jstring JNICALL
Java_com_ndk_1demo_MainActivity_getFromC(JNIEnv *env, jclass type) {

    // TODO
    const char *s = "aaaaaaaaa";

    return env->NewStringUTF(s);
}


JNIEXPORT jstring JNICALL
Java_com_ndk_1demo_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ndk_1demo_MainActivity_initIDs(JNIEnv *env, jclass type) {

    // TODO
    mid = env->GetMethodID(type,"showToast","()V");

}

extern "C"
JNIEXPORT void JNICALL
Java_com_ndk_1demo_MainActivity_method(JNIEnv *env, jobject instance) {

    // TODO
    env->CallVoidMethod(instance,mid);

}

extern "C"
JNIEXPORT void JNICALL
Java_com_ndk_1demo_MainActivity_accessMethod(JNIEnv *env, jobject instance) {
    // TODO

    jclass jclz = env->GetObjectClass(instance);
    //得到方法名
    jmethodID  mid = env->GetMethodID(jclz,"showToast","()V");
    env->CallVoidMethod(instance,mid);
}


extern "C"
JNIEXPORT void JNICALL
Java_com_ndk_1demo_MainActivity_accessField2(JNIEnv *env, jobject jobj) {
    // TODO
    //得到jclass
    jclass  jclz = env->GetObjectClass(jobj);
    //得到field
    jfieldID fid = env->GetFieldID(jclz,"count","I");
    //通过fid得到int
    jint count = env->GetIntField(jobj,fid);
    //
    count = count+5;
    env->SetIntField(jobj,fid,count);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_ndk_1demo_MainActivity_accessField(JNIEnv *env, jobject instance) {
    // TODO
    //得到jclass
    jclass  jclz = env->GetObjectClass(instance);
    //得到field
    jfieldID fid = env->GetFieldID(jclz,"key","Ljava/lang/String;");
    //通过filed得到string
    jstring  jstr = (jstring) env->GetObjectField(instance, fid);
    //将jstring转化为c语言中的char*
    char *c_str = (char *) env->GetStringUTFChars(jstr, NULL);
    //对字符串进行操作
    //char h[30]="hhh";
    char *h;
    strcpy(h,"ss");
    strcat(h, c_str);
    //将c语言转化为jni
    jstring  new_str = env->NewStringUTF(h);
    env->SetObjectField(instance,fid,new_str);//为字段设值
    env->ReleaseStringUTFChars(new_str,c_str);//释放string
    return new_str;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_ndk_1demo_MainActivity_getFromC3(JNIEnv *env, jobject instance, jintArray arr_) {
    jint *arr = env->GetIntArrayElements(arr_, NULL);
    int i;
    int sum=0;
    for(i=0;i<5;i++){
        sum = arr[i]+sum;
    }
    // TODO
    env->ReleaseIntArrayElements(arr_, arr, 0);
    return sum;
}


extern "C"//extern "C"的主要作用就是为了能够正确实现C++代码调用其他C语言代码。加上extern "C"后，会指示编译器这部分代码按c语言的进行编译，而不是C++的。
JNIEXPORT jstring JNICALL
Java_com_ndk_1demo_MainActivity_getFromC2(JNIEnv *env, jobject instance, jstring input_) {

    const char *input = env->GetStringUTFChars(input_, NULL);
    if(input==NULL){
        return NULL;
    }
    // TODO
    //printf("%s\n",input);
    env->ReleaseStringUTFChars(input_, input);
    //const char *s = "aaaaaaaaa";
    return env->NewStringUTF(input);
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_ndk_1demo_MainActivity_accessStaticMethod(JNIEnv *env, jobject instance) {

    //得到jclass
    jclass jclz = env->GetObjectClass(instance);
    //得到静态方法的方法名
    jmethodID jmid = env->GetStaticMethodID(jclz,"maxNum","(II)I");
    //调用方法
    int max = env->CallStaticIntMethod(jclz,jmid,5,4);
    LOGE("LC %d",max);
    return max;

}
extern "C"
JNIEXPORT jobject JNICALL
Java_com_ndk_1demo_MainActivity_accessDateMethod(JNIEnv *env, jobject instance) {
    //通过类的路径从jvm里面找到对应的类
    jclass  jclz = env->FindClass("java/util/Date");
    //因为是构造函数，所以name都是<init>
    jmethodID jmid=env->GetMethodID(jclz,"<init>","()V");
    //实例话一个date对象
    jobject  jobj = env->NewObject(jclz,jmid);
    //得到date对象中的方法
    jmethodID tmid = env->GetMethodID(jclz,"getTime","()J");
    //调用其中方法
    jlong  time = env->CallLongMethod(jobj,tmid);
    LOGE("LCssssss time:%lld\n",time);
    return jobj;
}
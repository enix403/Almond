#ifdef _AD_ENABLE_PROFILING

    #if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
		#define _AD_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
		#define _AD_FUNC_SIG __PRETTY_FUNCTION__
	#elif (defined(__FUNCSIG__) || (_MSC_VER))
		#define _AD_FUNC_SIG __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
		#define _AD_FUNC_SIG __FUNCTION__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
		#define _AD_FUNC_SIG __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
		#define _AD_FUNC_SIG __func__
	#else
		#define _AD_FUNC_SIG "(Unknown _AD_FUNC_SIG)"
	#endif

#endif
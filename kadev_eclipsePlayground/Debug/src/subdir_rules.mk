################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
src/kairq.obj: /home/kamichal/m_repo/kamichalRepo/kadev/src/kairq.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"/km/ti/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -g --include_path="/km/ti/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev" --include_path= --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/src" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/eZ_include" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/kadisp" --include_path="/km/ti/c55xx_csl/inc" --define=c5515 --display_error_number --diag_warning=225 --ptrdiff_size=16 --printf_support=full --preproc_with_compile --preproc_dependency="src/kairq.pp" --obj_directory="src" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

src/main.obj: /home/kamichal/m_repo/kamichalRepo/kadev/src/main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"/km/ti/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -g --include_path="/km/ti/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev" --include_path= --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/src" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/eZ_include" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/kadisp" --include_path="/km/ti/c55xx_csl/inc" --define=c5515 --display_error_number --diag_warning=225 --ptrdiff_size=16 --printf_support=full --preproc_with_compile --preproc_dependency="src/main.pp" --obj_directory="src" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

src/rtc_ex.obj: /home/kamichal/m_repo/kamichalRepo/kadev/src/rtc_ex.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"/km/ti/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -g --include_path="/km/ti/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev" --include_path= --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/src" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/eZ_include" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/kadisp" --include_path="/km/ti/c55xx_csl/inc" --define=c5515 --display_error_number --diag_warning=225 --ptrdiff_size=16 --printf_support=full --preproc_with_compile --preproc_dependency="src/rtc_ex.pp" --obj_directory="src" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '



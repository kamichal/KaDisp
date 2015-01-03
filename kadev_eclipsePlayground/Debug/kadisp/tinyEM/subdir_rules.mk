################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
kadisp/tinyEM/CQueue.obj: /home/kamichal/m_repo/kamichalRepo/TinyEM/app/src/CQueue.cpp $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"/km/ti/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -g --include_path="/km/ti/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev" --include_path= --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/src" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/eZ_include" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/kadisp" --include_path="/km/ti/c55xx_csl/inc" --define=c5515 --display_error_number --diag_warning=225 --ptrdiff_size=16 --printf_support=full --preproc_with_compile --preproc_dependency="kadisp/tinyEM/CQueue.pp" --obj_directory="kadisp/tinyEM" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

kadisp/tinyEM/CTinyEM.obj: /home/kamichal/m_repo/kamichalRepo/TinyEM/app/src/CTinyEM.cpp $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"/km/ti/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -g --include_path="/km/ti/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev" --include_path= --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/src" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/eZ_include" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/kadisp" --include_path="/km/ti/c55xx_csl/inc" --define=c5515 --display_error_number --diag_warning=225 --ptrdiff_size=16 --printf_support=full --preproc_with_compile --preproc_dependency="kadisp/tinyEM/CTinyEM.pp" --obj_directory="kadisp/tinyEM" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '



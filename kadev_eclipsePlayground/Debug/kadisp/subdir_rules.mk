################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
kadisp/font_8x6_philippe.obj: /home/kamichal/m_repo/kamichalRepo/kadev/kadisp/font_8x6_philippe.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"/km/ti/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=huge -g --include_path="/km/ti/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/kadev_eclipsePlayground/src" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/eZ_include" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/kadisp" --define=c5515 --display_error_number --diag_warning=225 --ptrdiff_size=32 --preproc_with_compile --preproc_dependency="kadisp/font_8x6_philippe.pp" --obj_directory="kadisp" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

kadisp/kadisp.obj: /home/kamichal/m_repo/kamichalRepo/kadev/kadisp/kadisp.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"/km/ti/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=huge -g --include_path="/km/ti/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/kadev_eclipsePlayground/src" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/eZ_include" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/kadisp" --define=c5515 --display_error_number --diag_warning=225 --ptrdiff_size=32 --preproc_with_compile --preproc_dependency="kadisp/kadisp.pp" --obj_directory="kadisp" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

kadisp/osd9616.obj: /home/kamichal/m_repo/kamichalRepo/kadev/kadisp/osd9616.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"/km/ti/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=huge -g --include_path="/km/ti/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/kadev_eclipsePlayground/src" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/eZ_include" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/kadisp" --define=c5515 --display_error_number --diag_warning=225 --ptrdiff_size=32 --preproc_with_compile --preproc_dependency="kadisp/osd9616.pp" --obj_directory="kadisp" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '



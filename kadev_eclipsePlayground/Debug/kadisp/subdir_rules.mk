################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
kadisp/font_8x6_philippe.obj: /home/kamichal/m_repo/kamichalRepo/kadev/kadisp/font_8x6_philippe.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"/km/ti/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -g --include_path="/km/ti/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/kadev_eclipsePlayground/src" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/eZ_include" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/kadisp" --include_path="/km/ti/c55xx_csl/inc" --define=c5515 --display_error_number --diag_warning=225 --ptrdiff_size=16 --printf_support=full --preproc_with_compile --preproc_dependency="kadisp/font_8x6_philippe.pp" --obj_directory="kadisp" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

kadisp/kadisp.obj: /home/kamichal/m_repo/kamichalRepo/kadev/kadisp/kadisp.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"/km/ti/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -g --include_path="/km/ti/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/kadev_eclipsePlayground/src" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/eZ_include" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/kadisp" --include_path="/km/ti/c55xx_csl/inc" --define=c5515 --display_error_number --diag_warning=225 --ptrdiff_size=16 --printf_support=full --preproc_with_compile --preproc_dependency="kadisp/kadisp.pp" --obj_directory="kadisp" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

kadisp/kadisp_tests.obj: /home/kamichal/m_repo/kamichalRepo/kadev/kadisp/kadisp_tests.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"/km/ti/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -g --include_path="/km/ti/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/kadev_eclipsePlayground/src" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/eZ_include" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/kadisp" --include_path="/km/ti/c55xx_csl/inc" --define=c5515 --display_error_number --diag_warning=225 --ptrdiff_size=16 --printf_support=full --preproc_with_compile --preproc_dependency="kadisp/kadisp_tests.pp" --obj_directory="kadisp" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

kadisp/ssd1780_oled_cntrl.obj: /home/kamichal/m_repo/kamichalRepo/kadev/kadisp/ssd1780_oled_cntrl.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"/km/ti/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -g --include_path="/km/ti/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/kadev_eclipsePlayground/src" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/eZ_include" --include_path="/home/kamichal/m_repo/kamichalRepo/kadev/kadisp" --include_path="/km/ti/c55xx_csl/inc" --define=c5515 --display_error_number --diag_warning=225 --ptrdiff_size=16 --printf_support=full --preproc_with_compile --preproc_dependency="kadisp/ssd1780_oled_cntrl.pp" --obj_directory="kadisp" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '



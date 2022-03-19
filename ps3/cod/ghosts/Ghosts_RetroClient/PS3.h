#ifndef INCLUDES_H
#define INCLUDES_H

#pragma comment(lib, "cgc")
#pragma comment(lib, "control_console_ppu")
#pragma comment(lib, "cs")
#pragma comment(lib, "daisy_stub")
#pragma comment(lib, "dbg")
#pragma comment(lib, "dbg_gcm_method_check")
#pragma comment(lib, "dbg_libio_stub")
#pragma comment(lib, "dbgfont")
#pragma comment(lib, "dbgfont_gcm")
#pragma comment(lib, "dbgrsx")
#pragma comment(lib, "dmux_stub")
#pragma comment(lib, "face")
#pragma comment(lib, "fiber_stub")
#pragma comment(lib, "fios")
#pragma comment(lib, "font_stub")
#pragma comment(lib, "fontFT_stub")
#pragma comment(lib, "fontGcm")
#pragma comment(lib, "freetype_stub")
#pragma comment(lib, "freetypeTT_stub")
#pragma comment(lib, "fs_stub")
#pragma comment(lib, "ftp")
#pragma comment(lib, "gcm_cmd")
#pragma comment(lib, "gcm_cmdasm")
#pragma comment(lib, "gcm_cmddbg")
#pragma comment(lib, "gcm_gpad_stub")
#pragma comment(lib, "gcm_pm")
#pragma comment(lib, "gcm_sys_stub")
#pragma comment(lib, "gem_stub")
#pragma comment(lib, "gifdec_stub")
#pragma comment(lib, "head_tracker")
#pragma comment(lib, "http_stub")
#pragma comment(lib, "http_util_stub")
#pragma comment(lib, "io_stub")
#pragma comment(lib, "jpgdec_stub")
#pragma comment(lib, "jpgenc_stub")
#pragma comment(lib, "key2char_stub")
#pragma comment(lib, "l10n_stub")
#pragma comment(lib, "lv2_stub")
#pragma comment(lib, "lv2dbg_stub")
#pragma comment(lib, "m")
#pragma comment(lib, "m_stub")
#pragma comment(lib, "medi_stub")
#pragma comment(lib, "mic_stub")
#pragma comment(lib, "mixer")
#pragma comment(lib, "msmp3dec_ppu")
#pragma comment(lib, "msmp3dec_SPURS")
#pragma comment(lib, "mstreamSPURSAT3")
#pragma comment(lib, "mstreamSPURSMP3")
#pragma comment(lib, "mstreamThreadAT3")
#pragma comment(lib, "mstreamThreadMP3")
#pragma comment(lib, "mt19937")
#pragma comment(lib, "net_stub")
#pragma comment(lib, "netctl_stub")
#pragma comment(lib, "ovis_stub")
#pragma comment(lib, "padfilter")
#pragma comment(lib, "pamf_stub")
#pragma comment(lib, "perf")
#pragma comment(lib, "pngdec_stub")
#pragma comment(lib, "pngenc_stub")
#pragma comment(lib, "prof_stub")
#pragma comment(lib, "pthread")
#pragma comment(lib, "resc_stub")
#pragma comment(lib, "rtc_stub")
#pragma comment(lib, "rudp_stub")
#pragma comment(lib, "sail_rec_stub")
#pragma comment(lib, "sail_stub")
#pragma comment(lib, "scream")
#pragma comment(lib, "sheap_stub")
#pragma comment(lib, "snc")
#pragma comment(lib, "snd3")
#pragma comment(lib, "spudll_stub")
#pragma comment(lib, "spurs_jq_stub")
#pragma comment(lib, "spurs_stub")
#pragma comment(lib, "ssl_stub")
#pragma comment(lib, "stdc++")
#pragma comment(lib, "stdc++_stub")
#pragma comment(lib, "sync_stub")
#pragma comment(lib, "sync2_stub")
#pragma comment(lib, "synth2")
#pragma comment(lib, "syscall")
#pragma comment(lib, "sysmodule_stub")

//#include <assert.h>   /*C:\usr\local\cell\target\ppu\include\assert.h*/
#include <cell.h>   /*C:\usr\local\cell\target\ppu\include\cell.h*/
#include <complex.h>   /*C:\usr\local\cell\target\ppu\include\complex.h*/
#include <ctype.h>   /*C:\usr\local\cell\target\ppu\include\ctype.h*/
#include <dirent.h>   /*C:\usr\local\cell\target\ppu\include\dirent.h*/
#include <errno.h>   /*C:\usr\local\cell\target\ppu\include\errno.h*/
#include <fastmath.h>   /*C:\usr\local\cell\target\ppu\include\fastmath.h*/
#include <fcntl.h>   /*C:\usr\local\cell\target\ppu\include\fcntl.h*/
#include <fenv.h>   /*C:\usr\local\cell\target\ppu\include\fenv.h*/
#include <float.h>   /*C:\usr\local\cell\target\ppu\include\float.h*/
#include <inttypes.h>   /*C:\usr\local\cell\target\ppu\include\inttypes.h*/
#include <iso646.h>   /*C:\usr\local\cell\target\ppu\include\iso646.h*/
#include <libftp.h>   /*C:\usr\local\cell\target\ppu\include\libftp.h*/
#include <limits.h>   /*C:\usr\local\cell\target\ppu\include\limits.h*/
#include <locale.h>   /*C:\usr\local\cell\target\ppu\include\locale.h*/
#include <math.h>   /*C:\usr\local\cell\target\ppu\include\math.h*/
#include <mspace.h>   /*C:\usr\local\cell\target\ppu\include\mspace.h*/
#include <mt19937.h>   /*C:\usr\local\cell\target\ppu\include\mt19937.h*/
#include <netdb.h>   /*C:\usr\local\cell\target\ppu\include\netdb.h*/
#include <np.h>   /*C:\usr\local\cell\target\ppu\include\np.h*/
#include <ppu_altivec_internals.h>   /*C:\usr\local\cell\target\ppu\include\ppu_altivec_internals.h*/
#include <ppu_asm_intrinsics.h>   /*C:\usr\local\cell\target\ppu\include\ppu_asm_intrinsics.h*/
#include <pthread.h>   /*C:\usr\local\cell\target\ppu\include\pthread.h*/
#include <pthread_types.h>   /*C:\usr\local\cell\target\ppu\include\pthread_types.h*/
#include <sched.h>   /*C:\usr\local\cell\target\ppu\include\sched.h*/
#include <semaphore.h>   /*C:\usr\local\cell\target\ppu\include\semaphore.h*/
#include <setjmp.h>   /*C:\usr\local\cell\target\ppu\include\setjmp.h*/
#include <spu_printf.h>   /*C:\usr\local\cell\target\ppu\include\spu_printf.h*/
#include <stdarg.h>   /*C:\usr\local\cell\target\ppu\include\stdarg.h*/
#include <stdbool.h>   /*C:\usr\local\cell\target\ppu\include\stdbool.h*/
#include <stddef.h>   /*C:\usr\local\cell\target\ppu\include\stddef.h*/
#include <stdint.h>   /*C:\usr\local\cell\target\ppu\include\stdint.h*/
#include <stdio.h>   /*C:\usr\local\cell\target\ppu\include\stdio.h*/
#include <stdlib.h>   /*C:\usr\local\cell\target\ppu\include\stdlib.h*/
#include <string.h>   /*C:\usr\local\cell\target\ppu\include\string.h*/
#include <tgmath.h>   /*C:\usr\local\cell\target\ppu\include\tgmath.h*/
#include <time.h>   /*C:\usr\local\cell\target\ppu\include\time.h*/
#include <types.h>   /*C:\usr\local\cell\target\ppu\include\types.h*/
#include <unistd.h>   /*C:\usr\local\cell\target\ppu\include\unistd.h*/
#include <utime.h>   /*C:\usr\local\cell\target\ppu\include\utime.h*/
#include <wchar.h>   /*C:\usr\local\cell\target\ppu\include\wchar.h*/
#include <wctype.h>   /*C:\usr\local\cell\target\ppu\include\wctype.h*/
#include <xlocinfo.h>   /*C:\usr\local\cell\target\ppu\include\xlocinfo.h*/
#include <xmtx.h>   /*C:\usr\local\cell\target\ppu\include\xmtx.h*/
#include <xstate.h>   /*C:\usr\local\cell\target\ppu\include\xstate.h*/
#include <xstrxfrm.h>   /*C:\usr\local\cell\target\ppu\include\xstrxfrm.h*/
#include <xtinfo.h>   /*C:\usr\local\cell\target\ppu\include\xtinfo.h*/
#include <xtls.h>   /*C:\usr\local\cell\target\ppu\include\xtls.h*/
#include <xwcc.h>   /*C:\usr\local\cell\target\ppu\include\xwcc.h*/
#include <xwchar.h>   /*C:\usr\local\cell\target\ppu\include\xwchar.h*/
#include <xwcstod.h>   /*C:\usr\local\cell\target\ppu\include\xwcstod.h*/
#include <xwcsxfrm.h>   /*C:\usr\local\cell\target\ppu\include\xwcsxfrm.h*/
#include <xwstr.h>   /*C:\usr\local\cell\target\ppu\include\xwstr.h*/
#include <ymath.h>   /*C:\usr\local\cell\target\ppu\include\ymath.h*/
#include <yvals.h>   /*C:\usr\local\cell\target\ppu\include\yvals.h*/
#include <arpa\inet.h>   /*C:\usr\local\cell\target\ppu\include\arpa\inet.h*/
#include <cell\atomic.h>   /*C:\usr\local\cell\target\ppu\include\cell\atomic.h*/
#include <cell\audio.h>   /*C:\usr\local\cell\target\ppu\include\cell\audio.h*/
#include <cell\camera.h>   /*C:\usr\local\cell\target\ppu\include\cell\camera.h*/
#include <cell\cell_fs.h>   /*C:\usr\local\cell\target\ppu\include\cell\cell_fs.h*/
#include <cell\cgb.h>   /*C:\usr\local\cell\target\ppu\include\cell\cgb.h*/
#include <cell\codec.h>   /*C:\usr\local\cell\target\ppu\include\cell\codec.h*/
#include <cell\control_console.h>   /*C:\usr\local\cell\target\ppu\include\cell\control_console.h*/
#include <cell\daisy.h>   /*C:\usr\local\cell\target\ppu\include\cell\daisy.h*/
#include <cell\dbg.h>   /*C:\usr\local\cell\target\ppu\include\cell\dbg.h*/
#include <cell\dbgfont.h>   /*C:\usr\local\cell\target\ppu\include\cell\dbgfont.h*/
#include <cell\dbgrsx.h>   /*C:\usr\local\cell\target\ppu\include\cell\dbgrsx.h*/
#include <cell\dma.h>   /*C:\usr\local\cell\target\ppu\include\cell\dma.h*/
#include <cell\fios.h>   /*C:\usr\local\cell\target\ppu\include\cell\fios.h*/
#include <cell\font.h>   /*C:\usr\local\cell\target\ppu\include\cell\font.h*/
#include <cell\fontFT.h>   /*C:\usr\local\cell\target\ppu\include\cell\fontFT.h*/
#include <cell\fontGcm.h>   /*C:\usr\local\cell\target\ppu\include\cell\fontGcm.h*/
#include <cell\gcm.h>   /*C:\usr\local\cell\target\ppu\include\cell\gcm.h*/
#include <cell\gcm_pm.h>   /*C:\usr\local\cell\target\ppu\include\cell\gcm_pm.h*/
#include <cell\gem.h>   /*C:\usr\local\cell\target\ppu\include\cell\gem.h*/
#include <cell\http.h>   /*C:\usr\local\cell\target\ppu\include\cell\http.h*/
#include <cell\keyboard.h>   /*C:\usr\local\cell\target\ppu\include\cell\keyboard.h*/
#include <cell\l10n.h>   /*C:\usr\local\cell\target\ppu\include\cell\l10n.h*/
#include <cell\libkey2char.h>   /*C:\usr\local\cell\target\ppu\include\cell\libkey2char.h*/
#include <cell\mic.h>   /*C:\usr\local\cell\target\ppu\include\cell\mic.h*/
#include <cell\mixer.h>   /*C:\usr\local\cell\target\ppu\include\cell\mixer.h*/
#include <cell\mouse.h>   /*C:\usr\local\cell\target\ppu\include\cell\mouse.h*/
#include <cell\mstream.h>   /*C:\usr\local\cell\target\ppu\include\cell\mstream.h*/
#include <cell\ovis.h>   /*C:\usr\local\cell\target\ppu\include\cell\ovis.h*/
#include <cell\pad.h>   /*C:\usr\local\cell\target\ppu\include\cell\pad.h*/
#include <cell\padfilter.h>   /*C:\usr\local\cell\target\ppu\include\cell\padfilter.h*/
#include <cell\resc.h>   /*C:\usr\local\cell\target\ppu\include\cell\resc.h*/
#include <cell\rtc.h>   /*C:\usr\local\cell\target\ppu\include\cell\rtc.h*/
#include <cell\rudp.h>   /*C:\usr\local\cell\target\ppu\include\cell\rudp.h*/
#include <cell\sail.h>   /*C:\usr\local\cell\target\ppu\include\cell\sail.h*/
#include <cell\sail_rec.h>   /*C:\usr\local\cell\target\ppu\include\cell\sail_rec.h*/
#include <cell\scream.h>   /*C:\usr\local\cell\target\ppu\include\cell\scream.h*/
#include <cell\sheap.h>   /*C:\usr\local\cell\target\ppu\include\cell\sheap.h*/
#include <cell\snd3.h>   /*C:\usr\local\cell\target\ppu\include\cell\snd3.h*/
#include <cell\spudll.h>   /*C:\usr\local\cell\target\ppu\include\cell\spudll.h*/
#include <cell\ssl.h>   /*C:\usr\local\cell\target\ppu\include\cell\ssl.h*/
#include <cell\swcache.h>   /*C:\usr\local\cell\target\ppu\include\cell\swcache.h*/
#include <cell\sync.h>   /*C:\usr\local\cell\target\ppu\include\cell\sync.h*/
#include <cell\synth2.h>   /*C:\usr\local\cell\target\ppu\include\cell\synth2.h*/
#include <cell\sysmodule.h>   /*C:\usr\local\cell\target\ppu\include\cell\sysmodule.h*/
#include <cell\usbd.h>   /*C:\usr\local\cell\target\ppu\include\cell\usbd.h*/
#include <cell\usbpspcm.h>   /*C:\usr\local\cell\target\ppu\include\cell\usbpspcm.h*/
#include <cell\voice.h>   /*C:\usr\local\cell\target\ppu\include\cell\voice.h*/
#include <cell\voiceTypes.h>   /*C:\usr\local\cell\target\ppu\include\cell\voiceTypes.h*/
#include <cell\vpost.h>   /*C:\usr\local\cell\target\ppu\include\cell\vpost.h*/
#include <cell\codec\ac3_adapter.h>   /*C:\usr\local\cell\target\ppu\include\cell\codec\ac3_adapter.h*/
#include <cell\codec\adec.h>   /*C:\usr\local\cell\target\ppu\include\cell\codec\adec.h*/
#include <cell\codec\adec_base.h>   /*C:\usr\local\cell\target\ppu\include\cell\codec\adec_base.h*/
#include <cell\codec\adec_celp.h>   /*C:\usr\local\cell\target\ppu\include\cell\codec\adec_celp.h*/
#include <cell\codec\adec_celp8.h>   /*C:\usr\local\cell\target\ppu\include\cell\codec\adec_celp8.h*/
#include <cell\codec\adec_m4aac.h>   /*C:\usr\local\cell\target\ppu\include\cell\codec\adec_m4aac.h*/
#include <cell\codec\at3_adapter.h>   /*C:\usr\local\cell\target\ppu\include\cell\codec\at3_adapter.h*/
#include <cell\codec\atx_adapter.h>   /*C:\usr\local\cell\target\ppu\include\cell\codec\atx_adapter.h*/
#include <cell\codec\celp8enc.h>   /*C:\usr\local\cell\target\ppu\include\cell\codec\celp8enc.h*/
#include <cell\codec\celpenc.h>   /*C:\usr\local\cell\target\ppu\include\cell\codec\celpenc.h*/
#include <cell\codec\dmux.h>   /*C:\usr\local\cell\target\ppu\include\cell\codec\dmux.h*/
#include <cell\codec\dmux_pamf.h>   /*C:\usr\local\cell\target\ppu\include\cell\codec\dmux_pamf.h*/
#include <cell\codec\gifdec.h>   /*C:\usr\local\cell\target\ppu\include\cell\codec\gifdec.h*/
#include <cell\codec\jpgdec.h>   /*C:\usr\local\cell\target\ppu\include\cell\codec\jpgdec.h*/
#include <cell\codec\jpgenc.h>   /*C:\usr\local\cell\target\ppu\include\cell\codec\jpgenc.h*/
#include <cell\codec\libatrac3plus.h>   /*C:\usr\local\cell\target\ppu\include\cell\codec\libatrac3plus.h*/
#include <cell\codec\lpcm_adapter.h>   /*C:\usr\local\cell\target\ppu\include\cell\codec\lpcm_adapter.h*/
#include <cell\codec\mp3_adapter.h>   /*C:\usr\local\cell\target\ppu\include\cell\codec\mp3_adapter.h*/
#include <cell\codec\mpegbc_adapter.h>   /*C:\usr\local\cell\target\ppu\include\cell\codec\mpegbc_adapter.h*/
#include <cell\codec\pamf.h>   /*C:\usr\local\cell\target\ppu\include\cell\codec\pamf.h*/
#include <cell\codec\pngcom.h>   /*C:\usr\local\cell\target\ppu\include\cell\codec\pngcom.h*/
#include <cell\codec\pngdec.h>   /*C:\usr\local\cell\target\ppu\include\cell\codec\pngdec.h*/
#include <cell\codec\pngenc.h>   /*C:\usr\local\cell\target\ppu\include\cell\codec\pngenc.h*/
#include <cell\codec\types.h>   /*C:\usr\local\cell\target\ppu\include\cell\codec\types.h*/
#include <cell\codec\vdec.h>   /*C:\usr\local\cell\target\ppu\include\cell\codec\vdec.h*/
#include <cell\codec\vdec_avc.h>   /*C:\usr\local\cell\target\ppu\include\cell\codec\vdec_avc.h*/
#include <cell\codec\vdec_divx.h>   /*C:\usr\local\cell\target\ppu\include\cell\codec\vdec_divx.h*/
#include <cell\codec\vdec_mpeg2.h>   /*C:\usr\local\cell\target\ppu\include\cell\codec\vdec_mpeg2.h*/
#include <cell\console\console.h>   /*C:\usr\local\cell\target\ppu\include\cell\console\console.h*/
#include <cell\console\io\deci3.h>   /*C:\usr\local\cell\target\ppu\include\cell\console\io\deci3.h*/
#include <cell\console\io\network.h>   /*C:\usr\local\cell\target\ppu\include\cell\console\io\network.h*/
#include <cell\console\plugins\performance_data.h>   /*C:\usr\local\cell\target\ppu\include\cell\console\plugins\performance_data.h*/
#include <cell\console\plugins\screen_shot.h>   /*C:\usr\local\cell\target\ppu\include\cell\console\plugins\screen_shot.h*/
#include <cell\console\plugins\variable_tracker.h>   /*C:\usr\local\cell\target\ppu\include\cell\console\plugins\variable_tracker.h*/
#include <cell\daisy\lfqueue2.h>   /*C:\usr\local\cell\target\ppu\include\cell\daisy\lfqueue2.h*/
#include <cell\daisy\sync_pipe_interlock.h>   /*C:\usr\local\cell\target\ppu\include\cell\daisy\sync_pipe_interlock.h*/
#include <cell\dbgrsx\dbgrsx_bundle_state_struct.h>   /*C:\usr\local\cell\target\ppu\include\cell\dbgrsx\dbgrsx_bundle_state_struct.h*/
#include <cell\dbgrsx\dbgrsx_enum.h>   /*C:\usr\local\cell\target\ppu\include\cell\dbgrsx\dbgrsx_enum.h*/
#include <cell\dbgrsx\dbgrsx_error.h>   /*C:\usr\local\cell\target\ppu\include\cell\dbgrsx\dbgrsx_error.h*/
#include <cell\dbgrsx\dbgrsx_struct.h>   /*C:\usr\local\cell\target\ppu\include\cell\dbgrsx\dbgrsx_struct.h*/
#include <cell\fiber\ppuUtilDefine.h>   /*C:\usr\local\cell\target\ppu\include\cell\fiber\ppuUtilDefine.h*/
#include <cell\fiber\ppuUtilRuntime.h>   /*C:\usr\local\cell\target\ppu\include\cell\fiber\ppuUtilRuntime.h*/
#include <cell\fiber\ppu_context.h>   /*C:\usr\local\cell\target\ppu\include\cell\fiber\ppu_context.h*/
#include <cell\fiber\ppu_fiber.h>   /*C:\usr\local\cell\target\ppu\include\cell\fiber\ppu_fiber.h*/
#include <cell\fiber\ppu_fiber_trace.h>   /*C:\usr\local\cell\target\ppu\include\cell\fiber\ppu_fiber_trace.h*/
#include <cell\fiber\ppu_initialize.h>   /*C:\usr\local\cell\target\ppu\include\cell\fiber\ppu_initialize.h*/
#include <cell\fiber\user_scheduler.h>   /*C:\usr\local\cell\target\ppu\include\cell\fiber\user_scheduler.h*/
#include <cell\fios\fios_base.h>   /*C:\usr\local\cell\target\ppu\include\cell\fios\fios_base.h*/
#include <cell\fios\fios_caching.h>   /*C:\usr\local\cell\target\ppu\include\cell\fios\fios_caching.h*/
#include <cell\fios\fios_collections.h>   /*C:\usr\local\cell\target\ppu\include\cell\fios\fios_collections.h*/
#include <cell\fios\fios_common.h>   /*C:\usr\local\cell\target\ppu\include\cell\fios\fios_common.h*/
#include <cell\fios\fios_configuration.h>   /*C:\usr\local\cell\target\ppu\include\cell\fios\fios_configuration.h*/
#include <cell\fios\fios_dearchive.h>   /*C:\usr\local\cell\target\ppu\include\cell\fios\fios_dearchive.h*/
#include <cell\fios\fios_decompressor.h>   /*C:\usr\local\cell\target\ppu\include\cell\fios\fios_decompressor.h*/
#include <cell\fios\fios_emulation.h>   /*C:\usr\local\cell\target\ppu\include\cell\fios\fios_emulation.h*/
#include <cell\fios\fios_filehandle.h>   /*C:\usr\local\cell\target\ppu\include\cell\fios\fios_filehandle.h*/
#include <cell\fios\fios_media.h>   /*C:\usr\local\cell\target\ppu\include\cell\fios\fios_media.h*/
#include <cell\fios\fios_memory.h>   /*C:\usr\local\cell\target\ppu\include\cell\fios\fios_memory.h*/
#include <cell\fios\fios_op.h>   /*C:\usr\local\cell\target\ppu\include\cell\fios\fios_op.h*/
#include <cell\fios\fios_overlay.h>   /*C:\usr\local\cell\target\ppu\include\cell\fios\fios_overlay.h*/
#include <cell\fios\fios_paths.h>   /*C:\usr\local\cell\target\ppu\include\cell\fios\fios_paths.h*/
#include <cell\fios\fios_platform.h>   /*C:\usr\local\cell\target\ppu\include\cell\fios\fios_platform.h*/
#include <cell\fios\fios_platform_imp.h>   /*C:\usr\local\cell\target\ppu\include\cell\fios\fios_platform_imp.h*/
#include <cell\fios\fios_scheduler.h>   /*C:\usr\local\cell\target\ppu\include\cell\fios\fios_scheduler.h*/
#include <cell\fios\fios_time.h>   /*C:\usr\local\cell\target\ppu\include\cell\fios\fios_time.h*/
#include <cell\fios\fios_types.h>   /*C:\usr\local\cell\target\ppu\include\cell\fios\fios_types.h*/
#include <cell\fios\fios_watch.h>   /*C:\usr\local\cell\target\ppu\include\cell\fios\fios_watch.h*/
#include <cell\fios\ps3\ppu\fios_media_ps3ppu.h>   /*C:\usr\local\cell\target\ppu\include\cell\fios\ps3\ppu\fios_media_ps3ppu.h*/
#include <cell\fios\ps3\ppu\fios_platform_imp_ps3ppu.h>   /*C:\usr\local\cell\target\ppu\include\cell\fios\ps3\ppu\fios_platform_imp_ps3ppu.h*/
#include <cell\fios\ps3\ppu\fios_ps3ppu.h>   /*C:\usr\local\cell\target\ppu\include\cell\fios\ps3\ppu\fios_ps3ppu.h*/
#include <cell\font\error.h>   /*C:\usr\local\cell\target\ppu\include\cell\font\error.h*/
#include <cell\font\libfont.h>   /*C:\usr\local\cell\target\ppu\include\cell\font\libfont.h*/
#include <cell\font\libfontFT.h>   /*C:\usr\local\cell\target\ppu\include\cell\font\libfontFT.h*/
#include <cell\font\libfontGcm.h>   /*C:\usr\local\cell\target\ppu\include\cell\font\libfontGcm.h*/
#include <cell\font\ps3fontset.h>   /*C:\usr\local\cell\target\ppu\include\cell\font\ps3fontset.h*/
#include <cell\fs\cell_fs_errno.h>   /*C:\usr\local\cell\target\ppu\include\cell\fs\cell_fs_errno.h*/
#include <cell\fs\cell_fs_file_api.h>   /*C:\usr\local\cell\target\ppu\include\cell\fs\cell_fs_file_api.h*/
#include <cell\gem\libgem.h>   /*C:\usr\local\cell\target\ppu\include\cell\gem\libgem.h*/
#include <cell\hash\libhash.h>   /*C:\usr\local\cell\target\ppu\include\cell\hash\libhash.h*/
#include <cell\hash\libmd5.h>   /*C:\usr\local\cell\target\ppu\include\cell\hash\libmd5.h*/
#include <cell\hash\libmd5SPURS.h>   /*C:\usr\local\cell\target\ppu\include\cell\hash\libmd5SPURS.h*/
#include <cell\hash\libsha1.h>   /*C:\usr\local\cell\target\ppu\include\cell\hash\libsha1.h*/
#include <cell\hash\libsha1SPURS.h>   /*C:\usr\local\cell\target\ppu\include\cell\hash\libsha1SPURS.h*/
#include <cell\hash\libsha224.h>   /*C:\usr\local\cell\target\ppu\include\cell\hash\libsha224.h*/
#include <cell\hash\libsha224SPURS.h>   /*C:\usr\local\cell\target\ppu\include\cell\hash\libsha224SPURS.h*/
#include <cell\hash\libsha256.h>   /*C:\usr\local\cell\target\ppu\include\cell\hash\libsha256.h*/
#include <cell\hash\libsha256SPURS.h>   /*C:\usr\local\cell\target\ppu\include\cell\hash\libsha256SPURS.h*/
#include <cell\hash\libsha384.h>   /*C:\usr\local\cell\target\ppu\include\cell\hash\libsha384.h*/
#include <cell\hash\libsha384SPURS.h>   /*C:\usr\local\cell\target\ppu\include\cell\hash\libsha384SPURS.h*/
#include <cell\hash\libsha512.h>   /*C:\usr\local\cell\target\ppu\include\cell\hash\libsha512.h*/
#include <cell\hash\libsha512SPURS.h>   /*C:\usr\local\cell\target\ppu\include\cell\hash\libsha512SPURS.h*/
#include <cell\http\client.h>   /*C:\usr\local\cell\target\ppu\include\cell\http\client.h*/
#include <cell\http\error.h>   /*C:\usr\local\cell\target\ppu\include\cell\http\error.h*/
#include <cell\http\net_error.h>   /*C:\usr\local\cell\target\ppu\include\cell\http\net_error.h*/
#include <cell\http\util.h>   /*C:\usr\local\cell\target\ppu\include\cell\http\util.h*/
#include <cell\keyboard\error.h>   /*C:\usr\local\cell\target\ppu\include\cell\keyboard\error.h*/
#include <cell\keyboard\kb_codes.h>   /*C:\usr\local\cell\target\ppu\include\cell\keyboard\kb_codes.h*/
#include <cell\keyboard\libkb.h>   /*C:\usr\local\cell\target\ppu\include\cell\keyboard\libkb.h*/
#include <cell\mic\define.h>   /*C:\usr\local\cell\target\ppu\include\cell\mic\define.h*/
#include <cell\mic\error.h>   /*C:\usr\local\cell\target\ppu\include\cell\mic\error.h*/
#include <cell\mic\interface.h>   /*C:\usr\local\cell\target\ppu\include\cell\mic\interface.h*/
#include <cell\mixer\define.h>   /*C:\usr\local\cell\target\ppu\include\cell\mixer\define.h*/
#include <cell\mixer\error.h>   /*C:\usr\local\cell\target\ppu\include\cell\mixer\error.h*/
#include <cell\mouse\error.h>   /*C:\usr\local\cell\target\ppu\include\cell\mouse\error.h*/
#include <cell\mouse\libmouse.h>   /*C:\usr\local\cell\target\ppu\include\cell\mouse\libmouse.h*/
#include <cell\mouse\mouse_codes.h>   /*C:\usr\local\cell\target\ppu\include\cell\mouse\mouse_codes.h*/
#include <cell\ovis\error.h>   /*C:\usr\local\cell\target\ppu\include\cell\ovis\error.h*/
#include <cell\ovis\util.h>   /*C:\usr\local\cell\target\ppu\include\cell\ovis\util.h*/
#include <cell\pad\error.h>   /*C:\usr\local\cell\target\ppu\include\cell\pad\error.h*/
#include <cell\pad\libpad.h>   /*C:\usr\local\cell\target\ppu\include\cell\pad\libpad.h*/
#include <cell\pad\libpad_dbg.h>   /*C:\usr\local\cell\target\ppu\include\cell\pad\libpad_dbg.h*/
#include <cell\pad\pad_codes.h>   /*C:\usr\local\cell\target\ppu\include\cell\pad\pad_codes.h*/
#include <cell\perf\performance.h>   /*C:\usr\local\cell\target\ppu\include\cell\perf\performance.h*/
#include <cell\rtc\error.h>   /*C:\usr\local\cell\target\ppu\include\cell\rtc\error.h*/
#include <cell\rtc\rtcsvc.h>   /*C:\usr\local\cell\target\ppu\include\cell\rtc\rtcsvc.h*/
#include <cell\sail\au_receiver.h>   /*C:\usr\local\cell\target\ppu\include\cell\sail\au_receiver.h*/
#include <cell\sail\avi.h>   /*C:\usr\local\cell\target\ppu\include\cell\sail\avi.h*/
#include <cell\sail\common.h>   /*C:\usr\local\cell\target\ppu\include\cell\sail\common.h*/
#include <cell\sail\common_rec.h>   /*C:\usr\local\cell\target\ppu\include\cell\sail\common_rec.h*/
#include <cell\sail\converter.h>   /*C:\usr\local\cell\target\ppu\include\cell\sail\converter.h*/
#include <cell\sail\descriptor.h>   /*C:\usr\local\cell\target\ppu\include\cell\sail\descriptor.h*/
#include <cell\sail\feeder_audio.h>   /*C:\usr\local\cell\target\ppu\include\cell\sail\feeder_audio.h*/
#include <cell\sail\feeder_video.h>   /*C:\usr\local\cell\target\ppu\include\cell\sail\feeder_video.h*/
#include <cell\sail\graphics_adapter.h>   /*C:\usr\local\cell\target\ppu\include\cell\sail\graphics_adapter.h*/
#include <cell\sail\mp4.h>   /*C:\usr\local\cell\target\ppu\include\cell\sail\mp4.h*/
#include <cell\sail\player.h>   /*C:\usr\local\cell\target\ppu\include\cell\sail\player.h*/
#include <cell\sail\profile.h>   /*C:\usr\local\cell\target\ppu\include\cell\sail\profile.h*/
#include <cell\sail\recorder.h>   /*C:\usr\local\cell\target\ppu\include\cell\sail\recorder.h*/
#include <cell\sail\renderer_audio.h>   /*C:\usr\local\cell\target\ppu\include\cell\sail\renderer_audio.h*/
#include <cell\sail\renderer_video.h>   /*C:\usr\local\cell\target\ppu\include\cell\sail\renderer_video.h*/
#include <cell\sail\sound_adapter.h>   /*C:\usr\local\cell\target\ppu\include\cell\sail\sound_adapter.h*/
#include <cell\sail\source.h>   /*C:\usr\local\cell\target\ppu\include\cell\sail\source.h*/
#include <cell\sail\source_check.h>   /*C:\usr\local\cell\target\ppu\include\cell\sail\source_check.h*/
#include <cell\scream\legacy.h>   /*C:\usr\local\cell\target\ppu\include\cell\scream\legacy.h*/
#include <cell\sheap\error.h>   /*C:\usr\local\cell\target\ppu\include\cell\sheap\error.h*/
#include <cell\sheap\key_sheap.h>   /*C:\usr\local\cell\target\ppu\include\cell\sheap\key_sheap.h*/
#include <cell\sheap\key_sheap_barrier.h>   /*C:\usr\local\cell\target\ppu\include\cell\sheap\key_sheap_barrier.h*/
#include <cell\sheap\key_sheap_buffer.h>   /*C:\usr\local\cell\target\ppu\include\cell\sheap\key_sheap_buffer.h*/
#include <cell\sheap\key_sheap_mutex.h>   /*C:\usr\local\cell\target\ppu\include\cell\sheap\key_sheap_mutex.h*/
#include <cell\sheap\key_sheap_queue.h>   /*C:\usr\local\cell\target\ppu\include\cell\sheap\key_sheap_queue.h*/
#include <cell\sheap\key_sheap_rwm.h>   /*C:\usr\local\cell\target\ppu\include\cell\sheap\key_sheap_rwm.h*/
#include <cell\sheap\key_sheap_semaphore.h>   /*C:\usr\local\cell\target\ppu\include\cell\sheap\key_sheap_semaphore.h*/
#include <cell\sheap\sheap_base.h>   /*C:\usr\local\cell\target\ppu\include\cell\sheap\sheap_base.h*/
#include <cell\ssl\cert.h>   /*C:\usr\local\cell\target\ppu\include\cell\ssl\cert.h*/
#include <cell\ssl\error.h>   /*C:\usr\local\cell\target\ppu\include\cell\ssl\error.h*/
#include <cell\ssl\ssl.h>   /*C:\usr\local\cell\target\ppu\include\cell\ssl\ssl.h*/
#include <cell\sync\barrier.h>   /*C:\usr\local\cell\target\ppu\include\cell\sync\barrier.h*/
#include <cell\sync\error.h>   /*C:\usr\local\cell\target\ppu\include\cell\sync\error.h*/
#include <cell\sync\lfqueue.h>   /*C:\usr\local\cell\target\ppu\include\cell\sync\lfqueue.h*/
#include <cell\sync\mutex.h>   /*C:\usr\local\cell\target\ppu\include\cell\sync\mutex.h*/
#include <cell\sync\queue.h>   /*C:\usr\local\cell\target\ppu\include\cell\sync\queue.h*/
#include <cell\sync\rwm.h>   /*C:\usr\local\cell\target\ppu\include\cell\sync\rwm.h*/
#include <cell\sync2\cond.h>   /*C:\usr\local\cell\target\ppu\include\cell\sync2\cond.h*/
#include <cell\sync2\mutex.h>   /*C:\usr\local\cell\target\ppu\include\cell\sync2\mutex.h*/
#include <cell\sync2\queue.h>   /*C:\usr\local\cell\target\ppu\include\cell\sync2\queue.h*/
#include <cell\sync2\semaphore.h>   /*C:\usr\local\cell\target\ppu\include\cell\sync2\semaphore.h*/
#include <cell\sync2\thread.h>   /*C:\usr\local\cell\target\ppu\include\cell\sync2\thread.h*/
#include <cell\synth2\sd_compat.h>   /*C:\usr\local\cell\target\ppu\include\cell\synth2\sd_compat.h*/
#include <cell\usbd\error.h>   /*C:\usr\local\cell\target\ppu\include\cell\usbd\error.h*/
#include <cell\usbd\libusbd.h>   /*C:\usr\local\cell\target\ppu\include\cell\usbd\libusbd.h*/
#include <cell\usbd\usb.h>   /*C:\usr\local\cell\target\ppu\include\cell\usbd\usb.h*/
#include <GLES\egl.h>   /*C:\usr\local\cell\target\ppu\include\GLES\egl.h*/
#include <GLES\gl.h>   /*C:\usr\local\cell\target\ppu\include\GLES\gl.h*/
#include <GLES\glext.h>   /*C:\usr\local\cell\target\ppu\include\GLES\glext.h*/
#include <net\if_dl.h>   /*C:\usr\local\cell\target\ppu\include\net\if_dl.h*/
#include <net\if_types.h>   /*C:\usr\local\cell\target\ppu\include\net\if_types.h*/
#include <netex\errno.h>   /*C:\usr\local\cell\target\ppu\include\netex\errno.h*/
#include <netex\ifctl.h>   /*C:\usr\local\cell\target\ppu\include\netex\ifctl.h*/
#include <netex\libnetctl.h>   /*C:\usr\local\cell\target\ppu\include\netex\libnetctl.h*/
#include <netex\net.h>   /*C:\usr\local\cell\target\ppu\include\netex\net.h*/
#include <netex\ns.h>   /*C:\usr\local\cell\target\ppu\include\netex\ns.h*/
#include <netex\sockinfo.h>   /*C:\usr\local\cell\target\ppu\include\netex\sockinfo.h*/
#include <netex\udpp2p.h>   /*C:\usr\local\cell\target\ppu\include\netex\udpp2p.h*/
#include <netinet\icmp.h>   /*C:\usr\local\cell\target\ppu\include\netinet\icmp.h*/
#include <netinet\in.h>   /*C:\usr\local\cell\target\ppu\include\netinet\in.h*/
#include <netinet\ip.h>   /*C:\usr\local\cell\target\ppu\include\netinet\ip.h*/
#include <netinet\tcp.h>   /*C:\usr\local\cell\target\ppu\include\netinet\tcp.h*/
#include <np\basic.h>   /*C:\usr\local\cell\target\ppu\include\np\basic.h*/
#include <np\clans.h>   /*C:\usr\local\cell\target\ppu\include\np\clans.h*/
#include <np\commerce2.h>   /*C:\usr\local\cell\target\ppu\include\np\commerce2.h*/
#include <np\common.h>   /*C:\usr\local\cell\target\ppu\include\np\common.h*/
#include <np\custom_menu.h>   /*C:\usr\local\cell\target\ppu\include\np\custom_menu.h*/
#include <np\drm.h>   /*C:\usr\local\cell\target\ppu\include\np\drm.h*/
#include <np\drm_inline.h>   /*C:\usr\local\cell\target\ppu\include\np\drm_inline.h*/
#include <np\error.h>   /*C:\usr\local\cell\target\ppu\include\np\error.h*/
#include <np\friendlist.h>   /*C:\usr\local\cell\target\ppu\include\np\friendlist.h*/
#include <np\lookup.h>   /*C:\usr\local\cell\target\ppu\include\np\lookup.h*/
#include <np\manager.h>   /*C:\usr\local\cell\target\ppu\include\np\manager.h*/
#include <np\matching2.h>   /*C:\usr\local\cell\target\ppu\include\np\matching2.h*/
#include <np\profile.h>   /*C:\usr\local\cell\target\ppu\include\np\profile.h*/
#include <np\ranking.h>   /*C:\usr\local\cell\target\ppu\include\np\ranking.h*/
#include <np\signaling.h>   /*C:\usr\local\cell\target\ppu\include\np\signaling.h*/
#include <np\sns.h>   /*C:\usr\local\cell\target\ppu\include\np\sns.h*/
#include <np\ticket.h>   /*C:\usr\local\cell\target\ppu\include\np\ticket.h*/
#include <np\trophy.h>   /*C:\usr\local\cell\target\ppu\include\np\trophy.h*/
#include <np\tustorage.h>   /*C:\usr\local\cell\target\ppu\include\np\tustorage.h*/
#include <np\util.h>   /*C:\usr\local\cell\target\ppu\include\np\util.h*/
#include <PSGL\deprecated.h>   /*C:\usr\local\cell\target\ppu\include\PSGL\deprecated.h*/
#include <PSGL\export.h>   /*C:\usr\local\cell\target\ppu\include\PSGL\export.h*/
#include <PSGL\psgl.h>   /*C:\usr\local\cell\target\ppu\include\PSGL\psgl.h*/
#include <PSGL\psglu.h>   /*C:\usr\local\cell\target\ppu\include\PSGL\psglu.h*/
#include <PSGL\report.h>   /*C:\usr\local\cell\target\ppu\include\PSGL\report.h*/
#include <sys\ansi.h>   /*C:\usr\local\cell\target\ppu\include\sys\ansi.h*/
#include <sys\cdefs.h>   /*C:\usr\local\cell\target\ppu\include\sys\cdefs.h*/
#include <sys\console.h>   /*C:\usr\local\cell\target\ppu\include\sys\console.h*/
#include <sys\dbg.h>   /*C:\usr\local\cell\target\ppu\include\sys\dbg.h*/
#include <sys\deci3.h>   /*C:\usr\local\cell\target\ppu\include\sys\deci3.h*/
#include <sys\event.h>   /*C:\usr\local\cell\target\ppu\include\sys\event.h*/
#include <sys\exportcplusplus.h>   /*C:\usr\local\cell\target\ppu\include\sys\exportcplusplus.h*/
#include <sys\fixed_addr.h>   /*C:\usr\local\cell\target\ppu\include\sys\fixed_addr.h*/
#include <sys\fs.h>   /*C:\usr\local\cell\target\ppu\include\sys\fs.h*/
#include <sys\fsw.h>   /*C:\usr\local\cell\target\ppu\include\sys\fsw.h*/
#include <sys\fs_external.h>   /*C:\usr\local\cell\target\ppu\include\sys\fs_external.h*/
#include <sys\gpio.h>   /*C:\usr\local\cell\target\ppu\include\sys\gpio.h*/
#include <sys\integertypes.h>   /*C:\usr\local\cell\target\ppu\include\sys\integertypes.h*/
#include <sys\interrupt.h>   /*C:\usr\local\cell\target\ppu\include\sys\interrupt.h*/
#include <sys\memory.h>   /*C:\usr\local\cell\target\ppu\include\sys\memory.h*/
#include <sys\mempool.h>   /*C:\usr\local\cell\target\ppu\include\sys\mempool.h*/
#include <sys\moduleexport.h>   /*C:\usr\local\cell\target\ppu\include\sys\moduleexport.h*/
#include <sys\mself_header.h>   /*C:\usr\local\cell\target\ppu\include\sys\mself_header.h*/
#include <sys\overlay.h>   /*C:\usr\local\cell\target\ppu\include\sys\overlay.h*/
#include <sys\paths.h>   /*C:\usr\local\cell\target\ppu\include\sys\paths.h*/
#include <sys\poll.h>   /*C:\usr\local\cell\target\ppu\include\sys\poll.h*/
#include <sys\ppu_thread.h>   /*C:\usr\local\cell\target\ppu\include\sys\ppu_thread.h*/
#include <sys\process.h>   /*C:\usr\local\cell\target\ppu\include\sys\process.h*/
#include <sys\prx.h>   /*C:\usr\local\cell\target\ppu\include\sys\prx.h*/
#include <sys\prx_error.h>   /*C:\usr\local\cell\target\ppu\include\sys\prx_error.h*/
#include <sys\random_number.h>   /*C:\usr\local\cell\target\ppu\include\sys\random_number.h*/
#include <sys\raw_spu.h>   /*C:\usr\local\cell\target\ppu\include\sys\raw_spu.h*/
#include <sys\return_code.h>   /*C:\usr\local\cell\target\ppu\include\sys\return_code.h*/
#include <sys\select.h>   /*C:\usr\local\cell\target\ppu\include\sys\select.h*/
#include <sys\socket.h>   /*C:\usr\local\cell\target\ppu\include\sys\socket.h*/
#include <sys\spinlock.h>   /*C:\usr\local\cell\target\ppu\include\sys\spinlock.h*/
#include <sys\spu_image.h>   /*C:\usr\local\cell\target\ppu\include\sys\spu_image.h*/
#include <sys\spu_initialize.h>   /*C:\usr\local\cell\target\ppu\include\sys\spu_initialize.h*/
#include <sys\spu_thread.h>   /*C:\usr\local\cell\target\ppu\include\sys\spu_thread.h*/
#include <sys\spu_thread_group.h>   /*C:\usr\local\cell\target\ppu\include\sys\spu_thread_group.h*/
#include <sys\spu_utility.h>   /*C:\usr\local\cell\target\ppu\include\sys\spu_utility.h*/
#include <sys\ss_get_open_psid.h>   /*C:\usr\local\cell\target\ppu\include\sys\ss_get_open_psid.h*/
#include <sys\stat.h>   /*C:\usr\local\cell\target\ppu\include\sys\stat.h*/
#include <sys\synchronization.h>   /*C:\usr\local\cell\target\ppu\include\sys\synchronization.h*/
#include <sys\syscall.h>   /*C:\usr\local\cell\target\ppu\include\sys\syscall.h*/
#include <sys\system_types.h>   /*C:\usr\local\cell\target\ppu\include\sys\system_types.h*/
#include <sys\sys_time.h>   /*C:\usr\local\cell\target\ppu\include\sys\sys_time.h*/
#include <sys\time.h>   /*C:\usr\local\cell\target\ppu\include\sys\time.h*/
#include <sys\timer.h>   /*C:\usr\local\cell\target\ppu\include\sys\timer.h*/
#include <sys\time_util.h>   /*C:\usr\local\cell\target\ppu\include\sys\time_util.h*/
#include <sys\tty.h>   /*C:\usr\local\cell\target\ppu\include\sys\tty.h*/
#include <sys\types.h>   /*C:\usr\local\cell\target\ppu\include\sys\types.h*/
#include <sys\vm.h>   /*C:\usr\local\cell\target\ppu\include\sys\vm.h*/
#include <sysutil\sysutil_ap.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_ap.h*/
#include <sysutil\sysutil_avc2.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_avc2.h*/
#include <sysutil\sysutil_avc2_video.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_avc2_video.h*/
#include <sysutil\sysutil_bgdl.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_bgdl.h*/
#include <sysutil\sysutil_bgmplayback.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_bgmplayback.h*/
#include <sysutil\sysutil_common.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_common.h*/
#include <sysutil\sysutil_gamecontent.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_gamecontent.h*/
#include <sysutil\sysutil_gameupdate.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_gameupdate.h*/
#include <sysutil\sysutil_game_common.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_game_common.h*/
#include <sysutil\sysutil_game_exec.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_game_exec.h*/
#include <sysutil\sysutil_imejp.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_imejp.h*/
#include <sysutil\sysutil_licensearea.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_licensearea.h*/
#include <sysutil\sysutil_msgdialog.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_msgdialog.h*/
#include <sysutil\sysutil_music.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_music.h*/
#include <sysutil\sysutil_music2.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_music2.h*/
#include <sysutil\sysutil_music_decode.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_music_decode.h*/
#include <sysutil\sysutil_music_decode2.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_music_decode2.h*/
#include <sysutil\sysutil_music_export.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_music_export.h*/
#include <sysutil\sysutil_music_playback_common.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_music_playback_common.h*/
#include <sysutil\sysutil_oskdialog.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_oskdialog.h*/
#include <sysutil\sysutil_oskdialog_ext.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_oskdialog_ext.h*/
#include <sysutil\sysutil_photo_decode.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_photo_decode.h*/
#include <sysutil\sysutil_photo_export.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_photo_export.h*/
#include <sysutil\sysutil_photo_import.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_photo_import.h*/
#include <sysutil\sysutil_print.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_print.h*/
#include <sysutil\sysutil_rec.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_rec.h*/
#include <sysutil\sysutil_remoteplay.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_remoteplay.h*/
#include <sysutil\sysutil_savedata.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_savedata.h*/
#include <sysutil\sysutil_screenshot.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_screenshot.h*/
#include <sysutil\sysutil_search.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_search.h*/
#include <sysutil\sysutil_search_types.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_search_types.h*/
#include <sysutil\sysutil_storagedata.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_storagedata.h*/
#include <sysutil\sysutil_subdisplay.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_subdisplay.h*/
#include <sysutil\sysutil_syscache.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_syscache.h*/
#include <sysutil\sysutil_sysconf.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_sysconf.h*/
#include <sysutil\sysutil_sysconf_ext.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_sysconf_ext.h*/
#include <sysutil\sysutil_sysparam.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_sysparam.h*/
#include <sysutil\sysutil_userinfo.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_userinfo.h*/
#include <sysutil\sysutil_video_export.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_video_export.h*/
#include <sysutil\sysutil_video_upload.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_video_upload.h*/
#include <sysutil\sysutil_webbrowser.h>   /*C:\usr\local\cell\target\ppu\include\sysutil\sysutil_webbrowser.h*/
#endif

SYS_MODULE_INFO(Ghosts_ImminentClient, 0, 1, 1);
SYS_MODULE_START(_entry);

#define GetPointer(X) *(int*)(X)

typedef unsigned char byte;
typedef unsigned char BYTE;
typedef unsigned char* PBYTE;
typedef void VOID;
typedef void* PVOID;
typedef long long __int64;
typedef unsigned int uint;

//PS3:
namespace PS3Lib
{
	float ReadSingleFloat(int Address)
	{
		return *(float*)Address;
	}

	float floatArray[100];
	float* ReadFloat(int address, int length)
	{
		for (int i = 0; i < length; i++)
		{
			floatArray[i] = *(float*)(address + (i * 0x04));
		}
		return floatArray;
	}

	char byteArrayz[100];
	char* ReadBytes(int address, int length)
	{
		for (int i = 0; i < length; i++)
		{
			byteArrayz[i] = *(char*)(address + (i));
		}
		return byteArrayz;
	}

	void WriteFloat(int address, float* input, int length)
	{
		for (int i = 0; i < length; i++)
		{
			*(float*)(address + (i * 4)) = input[i];
		}
	}

	void WriteSingleFloat(int Address, float Input)
	{
		*(float*)Address = Input;
	}

	void WriteBytes(int address, char* input, int length)
	{
		for (int i = 0; i < length; i++)
		{
			*(char*)(address + (i)) = input[i];
		}
	}

	void WriteByte(int Address, unsigned char Input)
	{
		*(unsigned char*)Address = Input;
	}

	float intArray[100];
	float* ReadInt(int address, int length)
	{
		for (int i = 0; i < length; i++)
		{
			intArray[i] = *(int*)(address + (i * 0x04));
		}
		return intArray;
	}

	void WriteInt(int address, int* input, int length)
	{
		for (int i = 0; i < length; i++)
		{
			*(int*)(intArray + (i * 0x04)) = input[i];
		}
	}

	void WriteInt32(int Address, int Input)
	{
		*(int*)Address = Input;
	}

	void WriteString(int address, char* string)
	{
		int FreeMem = 0x1D00000;
		int strlength = std::strlen(string);
		*(char**)FreeMem = string;
		char* StrBytes = ReadBytes(*(int*)FreeMem, strlength);
		WriteBytes(address, StrBytes, strlength);
	}

	struct readstr
	{
		char returnRead[100];
	}ReturnRead[1000];

	int strcount;
	char* ReadStringz(int address)
	{
		strcount++;
		memset(&ReturnRead[strcount].returnRead[0], 0, sizeof(ReturnRead[strcount].returnRead));
		int strlength = 100;
		char* StrBytes = ReadBytes(address, strlength);
		for (int i = 0; i < strlength; i++)
		{
			if (StrBytes[i] != 0x00)
				ReturnRead[strcount].returnRead[i] = StrBytes[i];
			else
				break;
		}
		return ReturnRead[strcount].returnRead;
	}

	char byteArray[100];
	char* ReadBytesC(int address, int length)
	{
		for (int i = 0; i < length; i++)
		{
			byteArray[i] = *(char*)(address + (i));
		}
		return byteArray;
	}

	char returnRead[100];
	char* ReadStringC(int address)
	{
		memset(&returnRead[0], 0, sizeof(returnRead));
		int strlength = 100;
		char* StrBytes = ReadBytesC(address, strlength);
		for (int i = 0; i < strlength; i++)
		{
			if (StrBytes[i] != 0x00)
				returnRead[i] = StrBytes[i];
			else
				break;
		}
		return returnRead;
	}

	int ReadInt32(int Address)
	{
		return *(int*)Address;
	}

	char* ReadString(int Address)
	{
		return (char*)Address;
	}

	char returnReadd[100];
	char* ReadStringzz(int address, bool IncludeSpaces) 
	{
		int strlength = 100;
		char* StrBytes = PS3Lib::ReadBytes(address, strlength);

		char StopBytes = 0x00;
		if (!IncludeSpaces)
			StopBytes = 0x20;

		for (int i = 0; i < strlength; i++)
			returnReadd[i] = 0;

		for (int i = 0; i < strlength; i++) 
		{
			if (StrBytes[i] != StopBytes)
				returnReadd[i] = StrBytes[i];
		}
		return returnReadd;
	}
};

//Console Commands
void sleep(usecond_t time) 
{
	sys_timer_usleep(time * 1000);
}

int console_write(const char * s) 
{
	int len = strlen(s);
	system_call_4(SYS_TTY_WRITE, 0, (uint64_t)s, len, (uint64_t)&len);
	return 0;
}

int32_t write_process(uint64_t ea, const void * data, uint32_t size)
{
	system_call_4(905, (uint64_t)sys_process_getpid(), ea, size, (uint64_t)data);
	return_to_user_prog(int32_t);
}

void* read_process(uint64_t ea, uint32_t size)
{
	void* data;
	system_call_4(904, (uint64_t)sys_process_getpid(), ea, size, (uint64_t)data);
	return data;
}

//Hook Functions
int Memcpy(void* destination, const void* source, size_t size)
{
	system_call_4(905, (uint64_t)sys_process_getpid(), (uint64_t)destination, size, (uint64_t)source);
	__dcbst(destination);
	__sync();
	__isync();
	return_to_user_prog(int);
}

void PatchInJump(int Address, int Destination)
{
	int FuncBytes[4];
	Destination = *(int*)Destination;
	FuncBytes[0] = 0x3D600000 + ((Destination >> 16) & 0xFFFF);
	if (Destination & 0x8000) FuncBytes[0] += 1;
	FuncBytes[1] = 0x396B0000 + (Destination & 0xFFFF);
	FuncBytes[2] = 0x7D6903A6;
	FuncBytes[3] = 0x4E800420;
	Memcpy((void*)Address, FuncBytes, 4 * 4);
}

void patcher(int Address, int Destination, bool Linked)
{
	int FuncBytes[4];
	Destination = *(int *)Destination;
	FuncBytes[0] = 0x3D600000 + ((Destination >> 16) & 0xFFFF);
	if (Destination & 0x8000)
		FuncBytes[0] += 1;
	FuncBytes[1] = 0x396B0000 + (Destination & 0xFFFF); // addi    %r11, %r11, dest&0xFFFF
	FuncBytes[2] = 0x7D6903A6; // mtctr    %r11
	FuncBytes[3] = 0x4E800420; // bctr
	if (Linked)
		FuncBytes[3] += 1; // bctrl
	Memcpy((void*)Address, FuncBytes, 4 * 4);
}

void hookFunctionStart(int Address, int saveStub, int Destination)
{
	saveStub = *(int*)saveStub;
	int BranchtoAddress = Address + (4 * 4);
	int StubData[8];
	StubData[0] = 0x3D600000 + ((BranchtoAddress >> 16) & 0xFFFF);
	if (BranchtoAddress & 0x8000) StubData[0] += 1;
	StubData[1] = 0x396B0000 + (BranchtoAddress & 0xFFFF);
	StubData[2] = 0x7D6903A6;
	Memcpy(&StubData[3], (void*)Address, 4 * 4);
	StubData[7] = 0x4E800420;
	Memcpy((void*)saveStub, StubData, 8 * 4);
	PatchInJump(Address, Destination);
}

void Menu_PaintAll_Stub(int a, int b)
{
	__asm("li %r3, 0x3");
}

// create thread
sys_ppu_thread_t id;
sys_ppu_thread_t create_thread(void(*entry)(uint64_t), int priority, size_t stacksize, const char* threadname)
{
	if (sys_ppu_thread_create(&id, entry, 0, priority, stacksize, 0, threadname) != CELL_OK)
	{
		console_write("Thread creation failed\n");
	}
	else
	{
		console_write("Thread created\n");
	}
	return id;
}

//Sprintf
void reverse(char s[])
{
	int i, j;
	char c;
	for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

void itoa(int n, char s[])
{
	int i, sign;
	if ((sign = n) < 0)  /* record sign */
		n = -n;          /* make n positive */
	i = 0;
	do  		/* generate digits in reverse order */
	{
		s[i++] = n % 10 + '0';	/* get next digit */
	} while ((n /= 10) > 0);	/* delete it */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

int catoi(const char* str)
{
	int val = 0;
	while (*str)
	{
		val = val * 10 + (*str++ - '0');
	}
	return val;
}

int atoi(char* str)
{
	int val = 0;
	while (*str)
	{
		val = val * 10 + (*str++ - '0');
	}
	return val;
}

bool isdigit(char Num)
{
	return (Num >= 0x30 && Num <= 0x39);
}

int VSprintf(char *ptr, const char *fmt, va_list ap)
{
	if (!ptr || !fmt)
		return -1;
	__int64 Int;
	int sLen;
	char* String;
	char* aPtr;
	byte bTemp;
	char Buf[0x500];
	while (*fmt)
	{
		char Temp = *fmt;
		int Length = -1;
		if (Temp == '%')
		{
			fmt++;
			if (*fmt == '0')
			{
				fmt++;
				Length = 0;
				char* aPtr = Buf;
				while (isdigit(Temp = *fmt))
				{
					*aPtr = Temp;
					aPtr++;
					fmt++;
					*aPtr = 0;
				}
				Length = atoi(Buf);
			}
			switch (*fmt)
			{
			case 's':
				String = va_arg(ap, char*);
				if (String)
				{
					while (*String)
					{
						*ptr = *String;
						String++;
						if (*String)
							ptr++;
					}
				}
				break;
			case 'p':
				Length = 8;
			case 'X':
			case 'x':
				bool Found;
				bool Caps;
				Int = va_arg(ap, __int64);
				if (Length == -1)
					Int = Int & 0xFFFFFFFF;
				Caps = *fmt != 'x';
				Found = false;
				for (int i = 0; i < 8; i++)   // for each bit :: 0 0   0 0   0 0   0 0
				{
					bTemp = (Int >> (28 - (i * 4))) & 0xF;
					if ((8 - i) <= Length)
						Found = true;
					if (Length == -1 && !Found && bTemp)
						Found = true;
					if (Found)
					{
						if (bTemp <= 9)// decimal
							*ptr = 0x30 + bTemp;
						else// hex
							*ptr = (Caps ? 0x40 : 0x60) + bTemp - 9;
						if (i != 7)
							*ptr++;
					}
				}
				break;
			case 'i':
			case 'd':
				memset(Buf, '0', 0xFF);
				Int = va_arg(ap, __int64);
				if (Length == -1)
					Int = Int & 0xFFFFFFFF;
				aPtr = ptr;
				itoa((int)Int, ptr);
				sLen = strlen(ptr);
				if (Length == -1)
					Length = sLen;
				memcpy(Buf + 0xFF - sLen, aPtr, sLen);
				memcpy(aPtr, Buf + 0xFF - Length, Length);
				ptr = aPtr + Length - 1;
				break;
			case 'f':
				break;
			}
		}
		else
			*ptr = Temp;
		ptr++;
		fmt++;
	}
	*ptr = 0;
	return 1;
}

int Sprintf(char *ptr, const char *fmt, /*args*/ ...) // %s, %i, %d, %x, %X, %p
{
	if (!ptr || !fmt)
		return -1;
	va_list ap;
	va_start(ap, fmt);
	VSprintf(ptr, fmt, ap);
	va_end(ap);
	return 1;
}

char vaBuffer[0x2000];
char* va(const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	VSprintf(vaBuffer, fmt, ap);

	va_end(ap);
	return vaBuffer;
}

// cString Compare
int cstrcmp(const char* s1, const char* s2) // 0 == strings are equal 
{
	while (*s1 && (*s1 == *s2))
		s1++, s2++;

	return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

bool Compare(const char* String1, const char* String2){
	return !strcmp(String1, String2);
}

// print commands
int cPrint(const char* string)
{
	char buf[100];
	Sprintf(buf, "%s\n", string);
	console_write(buf);
}

int clientIntPrint(int percentInt, const char* string)
{
	char buf[100];
	Sprintf(buf, "[%i] %s\n", percentInt, string);
	console_write(buf);
}

void Sleep(uint64_t ms)
{
	sys_timer_usleep(ms * 1000);
}

bool ok_dialog_result = false;
bool ok_dialog_input = false;

void OkDialogCallBack(int button_type, void *userdata)
{
	switch (button_type)
	{
	case CELL_MSGDIALOG_BUTTON_OK:
		ok_dialog_result = true;
		break;
	}
	ok_dialog_input = false;
}

bool DrawOkayMessageDialog(const char *format, ...)
{
	va_list argptr;
	char text[CELL_MSGDIALOG_STRING_SIZE];
	va_start(argptr, format);
	VSprintf(text, format, argptr);
	va_end(argptr);
	cellMsgDialogOpen2(CELL_MSGDIALOG_TYPE_SE_TYPE_NORMAL | CELL_MSGDIALOG_TYPE_BUTTON_TYPE_OK | CELL_MSGDIALOG_TYPE_DISABLE_CANCEL_ON | CELL_MSGDIALOG_TYPE_DEFAULT_CURSOR_OK, text, OkDialogCallBack, NULL, NULL);
	ok_dialog_input = true;
	while (ok_dialog_input)
	{
		Sleep(16);
		cellSysutilCheckCallback();
	}
	return ok_dialog_result;
}

void fixSpaces(char** szReturn)
{
	char *str = *szReturn;
	char _returnStr[512];// = (char*)Malloc(128);

	_returnStr[0] = '\0';

	int dwStrIndex = 0;

	for (int i = 0; i < strlen(str) + 1; i++)
	{
		if (str[i] != 0x20)
		{
			_returnStr[dwStrIndex] = str[i];
			dwStrIndex++;
		}
		else
		{
			_returnStr[dwStrIndex] = '%';
			_returnStr[dwStrIndex + 1] = '2';
			_returnStr[dwStrIndex + 2] = '0';
			dwStrIndex += 3;
		}


		_returnStr[dwStrIndex] = '\0';
	}

	*szReturn = _returnStr;
}

static int connect_to_webman(void)
{
	struct sockaddr_in sin;
	int s;

	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = 0x7F000001; //127.0.0.1 (localhost)
	sin.sin_port = htons(80);         //http port (80)
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0)
	{
		return -1;
	}

	if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
	{
		return -1;
	}

	return s;
}

static void sclose(int *socket_e)
{
	if (*socket_e != -1)
	{
		shutdown(*socket_e, SHUT_RDWR);
		socketclose(*socket_e);
		*socket_e = -1;
	}
}


static void send_wm_request(const char *cmd)
{
	// send command
	int conn_s = -1;
	conn_s = connect_to_webman();

	struct timeval tv;
	tv.tv_usec = 0;
	tv.tv_sec = 3;
	setsockopt(conn_s, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
	setsockopt(conn_s, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

	if (conn_s >= 0)
	{
		char wm_cmd[1048];
		int cmd_len = sprintf(wm_cmd, "GET %s HTTP/1.0\r\n", cmd);
		send(conn_s, wm_cmd, cmd_len, 0);
		sclose(&conn_s);
	}
}
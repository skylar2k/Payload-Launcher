#include "functions.hpp"


//https://github.com/Atmosphere-NX/Atmosphere/blob/6cc29185d24e2479e88650bb1c90ee4719b7e478/troposphere/reboot_to_payload/source/main.c#L7-L51
//============================================================================================
#define IRAM_PAYLOAD_MAX_SIZE 0x2F000
#define IRAM_PAYLOAD_BASE 0x40010000

alignas(0x1000) u8 g_reboot_payload[IRAM_PAYLOAD_MAX_SIZE];
alignas(0x1000) u8 g_ff_page[0x1000];
alignas(0x1000) u8 g_work_page[0x1000];

void do_iram_dram_copy(void* buf, uintptr_t iram_addr, size_t size, int option) {
	memcpy(g_work_page, buf, size);

	SecmonArgs args = { 0 };
	args.X[0] = 0xF0000201;             /* smcAmsIramCopy */
	args.X[1] = (uintptr_t)g_work_page;  /* DRAM Address */
	args.X[2] = iram_addr;              /* IRAM Address */
	args.X[3] = size;                   /* Copy size */
	args.X[4] = option;                 /* 0 = Read, 1 = Write */
	svcCallSecureMonitor(&args);

	memcpy(buf, g_work_page, size);
}

void copy_to_iram(uintptr_t iram_addr, void* buf, size_t size) {
	do_iram_dram_copy(buf, iram_addr, size, 1);
}

void copy_from_iram(void* buf, uintptr_t iram_addr, size_t size) {
	do_iram_dram_copy(buf, iram_addr, size, 0);
}

void clear_iram() {
	memset(g_ff_page, 0xFF, sizeof(g_ff_page));
	for (size_t i = 0; i < IRAM_PAYLOAD_MAX_SIZE; i += sizeof(g_ff_page)) {
		copy_to_iram(IRAM_PAYLOAD_BASE + i, g_ff_page, sizeof(g_ff_page));
	}
}

void reboot_to_payload() {
	clear_iram();

	for (size_t i = 0; i < IRAM_PAYLOAD_MAX_SIZE; i += 0x1000) {
		copy_to_iram(IRAM_PAYLOAD_BASE + i, &g_reboot_payload[i], 0x1000);
	}

	splSetConfig((SplConfigItem)65001, 2);
}
//============================================================================================

void rebootToPayload(const char* payload){
	Result sp = splInitialize();
	if(R_FAILED(sp)) return;

	FILE* f = fopen(payload,"rb");
	if (!f) return;

	fread(g_reboot_payload, 1, sizeof(g_reboot_payload), f);
    fclose(f);

	reboot_to_payload();
}

std::vector<std::string> getBins()
{
	std::vector<std::string> bins;

	if (auto dr = opendir("/payloads/.")) {
		while (auto f = readdir(dr)) {
			if (strstr(f->d_name,".bin") && !(strstr(f->d_name, "._"))){
				bins.push_back(f->d_name);
			}
		}
		closedir(dr);
	}

	return bins;
}

std::string getFavPayload(){
	CSimpleIniA ini;
	ini.SetUnicode();
	ini.LoadFile("sdmc:/payload-launcher.ini");

	return ini.GetValue("fpayload", "path", "default");
}

std::string writeFavPayload(const char* payload){
	CSimpleIniA ini;
	ini.SetUnicode();
	ini.LoadFile("sdmc:/payload-launcher.ini");
	ini.SetValue("fpayload", "path", payload);
	ini.SaveFile("sdmc:/payload-launcher.ini");

	return getFavPayload();
}
#include <Windows.h>
#include <Wincrypt.h>
#include <string>
#pragma comment(lib, "crypt32.lib")

#define PASSWORD "hogefuga"

// 参考記事
// - https://www.trustss.co.jp/smnEasyEnc1E0.html

int main(void) {
	HCRYPTPROV hProv;
	CryptAcquireContext(
		&hProv,
		NULL,
		MS_ENH_RSA_AES_PROV,
		PROV_RSA_AES,
		0);

	// 鍵生成
	// - 鍵生成には色んな方法があるのでここのAPIフックはあまり良い手じゃ無さげ
	HCRYPTHASH hHash;
	CryptCreateHash(
		hProv,
		CALG_SHA,
		0,
		0,
		&hHash);

	CryptHashData(
		hHash,
		(BYTE*)PASSWORD,
		(DWORD)strlen(PASSWORD),
		0);

	HCRYPTKEY hKey;
	CryptDeriveKey(
		hProv,
		CALG_AES_256,
		hHash,
		(256 << 16),
		&hKey);

	// 初期化ベクタや暗号モードの設定
	BYTE iv[16];
	memset(iv, 0, 16);
	CryptSetKeyParam(
		hKey,
		KP_IV,
		iv,
		0);

	DWORD mode = CRYPT_MODE_CBC;
	CryptSetKeyParam(
		hKey,
		KP_MODE,
		(BYTE*)&mode,
		0);

	// 復号鍵の作成
	// - 暗号化事にivが変化するため複製しとく
	HCRYPTKEY hdKey;
	CryptDuplicateKey(
		hKey,
		NULL,
		0,
		&hdKey);

	// 暗号化
	char data[100] = "hogehoge message.";
	printf("plain text: ");
	puts(data);
	DWORD dataLen = strlen(data)+1;
	CryptEncrypt(
		hKey,
		0,
		TRUE,
		0,
		(BYTE*)data,
		&dataLen,
		100);
	printf("enc text: ");
	puts(data);

	// 復号
	CryptDecrypt(
		hKey,
		0,
		TRUE,
		0,
		(BYTE*)data,
		&dataLen);
	printf("dec text: ");
	puts(data);

	CryptDestroyKey(hdKey);
	CryptDestroyKey(hKey);
	CryptDestroyKey(hHash);
	CryptReleaseContext(hProv, 0);
	return 0;
}

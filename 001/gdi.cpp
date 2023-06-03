#include "001.h"

void SaveImageFile( HBITMAP hBmp, WCHAR* filename )
{
	LONG imageSize;       // 画像サイズ
	BITMAPFILEHEADER fh;  // ビットマップファイルヘッダ
	BITMAPINFO* pbi;      // ビットマップ情報
	BITMAP bmp = { 0 };    // ビットマップ構造体
	LONG bpp;             // 画素数
	LPBYTE bits;          // 画像ビット
	HDC hdc;              // デバイスコンテキスト
	HDC hdc_mem;          // デバイスコンテキスト・メモリ
	HANDLE hFile;         // ファイラハンドル
	DWORD writeSize;      // 書き込んだサイズ

	// BITMAP情報を取得する
	GetObjectW( hBmp, sizeof( bmp ), &bmp );
	hdc = GetDC( 0 );
	hdc_mem = CreateCompatibleDC( hdc );
	ReleaseDC( 0, hdc );
	SelectObject( hdc_mem, hBmp );

	// ファイルサイズ計算
	imageSize = bmp.bmWidthBytes * bmp.bmHeight + sizeof( BITMAPFILEHEADER ) + sizeof( BITMAPINFOHEADER );
	switch ( bmp.bmBitsPixel )
	{
	case 2:
		bpp = 2;
		break;
	case 4:
		bpp = 16;
		break;
	case 8:
		bpp = 256;
		break;
	default:
		bpp = 0;
	}
	imageSize += ( sizeof( RGBQUAD ) * bpp );

	// BITMAPFILEHEADERヘッダー出力
	ZeroMemory( &fh, sizeof( fh ) );
	memcpy( &fh.bfType, "BM", 2 );
	fh.bfSize = imageSize;
	fh.bfReserved1 = 0;
	fh.bfReserved2 = 0;
	fh.bfOffBits = sizeof( BITMAPFILEHEADER ) + sizeof( BITMAPINFOHEADER )
		+ sizeof( RGBQUAD ) * bpp;

	// BITMAPINFOHEADERヘッダー出力
	pbi = new BITMAPINFO[ sizeof( BITMAPINFOHEADER ) + sizeof( RGBQUAD ) * bpp ];
	ZeroMemory( pbi, sizeof( BITMAPINFOHEADER ) );
	pbi->bmiHeader.biSize = sizeof( BITMAPINFOHEADER );
	pbi->bmiHeader.biWidth = bmp.bmWidth;
	pbi->bmiHeader.biHeight = bmp.bmHeight;
	pbi->bmiHeader.biPlanes = 1;
	pbi->bmiHeader.biBitCount = bmp.bmBitsPixel;
	pbi->bmiHeader.biCompression = BI_RGB;
	if ( bpp != 0 )
	{
		GetDIBColorTable( hdc_mem, 0, bpp, pbi->bmiColors );
	}

	// 画像データを得る
	bits = new BYTE[ bmp.bmWidthBytes * bmp.bmHeight ];
	GetDIBits( hdc_mem, hBmp, 0, bmp.bmHeight, bits, pbi, DIB_RGB_COLORS );

	// ファイルに書き込む
	hFile = CreateFileW( filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL );
	WriteFile( hFile, &fh, sizeof( fh ), &writeSize, NULL );
	WriteFile( hFile, pbi,
		sizeof( BITMAPINFOHEADER ) + sizeof( RGBQUAD ) * bpp, &writeSize, NULL );
	WriteFile( hFile, bits, bmp.bmWidthBytes * bmp.bmHeight, &writeSize, NULL );
	CloseHandle( hFile );

	// 開放
	delete[ ] pbi;
	delete[ ] bits;
	DeleteDC( hdc_mem );
}

HBITMAP GetHBITMAPFromImageFile( WCHAR* pFilePath )
{
	Gdiplus::GdiplusStartupInput gpStartupInput;
	ULONG_PTR gpToken;
	Gdiplus::GdiplusStartup( &gpToken, &gpStartupInput, NULL );
	HBITMAP result = NULL;
	Gdiplus::Bitmap* bitmap = Gdiplus::Bitmap::FromFile( pFilePath, false );
	if ( bitmap )
	{
		bitmap->GetHBITMAP( Gdiplus::Color( 255, 255, 255 ), &result );
		delete bitmap;
	}
	Gdiplus::GdiplusShutdown( gpToken );
	return result;
}

int GetEncoderClsid( const WCHAR* format, CLSID* pClsid )
{
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

	Gdiplus::GetImageEncodersSize( &num, &size );
	if ( size == 0 )
		return -1;  // Failure

	pImageCodecInfo = ( Gdiplus::ImageCodecInfo* ) ( malloc( size ) );
	if ( pImageCodecInfo == NULL )
		return -1;  // Failure

	GetImageEncoders( num, size, pImageCodecInfo );

	for ( UINT j = 0; j < num; ++j )
	{
		if ( wcscmp( pImageCodecInfo[ j ].MimeType, format ) == 0 )
		{
			*pClsid = pImageCodecInfo[ j ].Clsid;
			free( pImageCodecInfo );
			return j;  // Success
		}
	}

	free( pImageCodecInfo );
	return -1;  // Failure
}
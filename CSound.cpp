#include "CSound.h"
#include <stdlib.h>

//Constructor 
CSound::CSound()
{
	iChannel = -1;
	Sample = NULL;
}

//Libera memoria asignado al sonido
void CSound::FreeSound()
{
	FSOUND_Sample_Free(Sample);
}

// Cargamos desde un archivo el sonido
bool CSound::LoadSound(const char *filename)
{

	//Cargamos el sonido
	//El primer parametro es el numero de canal donde se cargara el sonido
	//lo mejor es pasarle FSOUND_FREE el cual elegira un canal libre
	//arbitrariamente
	//El segundo parametro es el nombre del sonido que vamos a cargar 
	//El tercer parametro es el formato del sonido nosotro le
	//pasamos FSOUND_STEREO 
	//Cuarto parametro es el desplazamiento del archivo, le pasamos 0
	//por que se esta cargando desde un archivo
	//Quinto parametro es la longitud del archivo, le pasamos 0
	Sample = FSOUND_Sample_Load(FSOUND_FREE, filename, FSOUND_MONO | FSOUND_STEREO, 0, 0);
	//Si existe algun error procesamos el error
	//y retorna false
	if (!Sample) {
		FSOUND_Close();
		return false;
	}
	return true;
}

bool CSound::IsSoundPlaying()
{
	signed char cPlaying;
	cPlaying = FSOUND_IsPlaying(iChannel);
	if (cPlaying == '1')
		return true;
	else
		return false;
}

// Reproducimos el sonido
void CSound::Play_Sound()
{
	//El primer parametro es el canal donde se reproducira
	//el sonido le pasamos FSOUND_FREE para que lo reproduzca
	//en un canal libre
	//El segundo parametro es un puntero al sonido
	//estamos reproduciendo y devuelve el canal
	//en el que se esta reproduciendo
	iChannel = FSOUND_PlaySound(FSOUND_FREE, Sample);
}

// Activamos/Desactivamos la pausa del sonido
void CSound::SetSoundPaused(bool bActivo)
{
	//El primer parametro es el canal al que
	//queremos hacer la pausa, 
	//El segundo parametro es bActivo que si es true 
	//realiza la pausa si no se desactiva la pausa
	FSOUND_SetPaused(iChannel, bActivo);
}

// Detenemos la reproduccion del sonido
void CSound::StopSound()
{
	//Se le pasa el numero de canal que queremos parar
	FSOUND_StopSound(iChannel);

}

//Fija el volumen del sonido
//debe estar entre 0 y 255
void CSound::SetSoundVolume(int iVol)
{
	//El primer parametro es el numero de canal
	//al que queremos modificar el volumen
	//El segundo parametro es el nuevo valor
	//del volumen debe estar entre 0 y 255
	FSOUND_SetVolume(iChannel, iVol);
}

//Activa o desctiva un loop al sonido
void CSound::SetSoundLoop(bool bActivo)
{
	//Si bActivo es true
	//Realiza un loop al sonido es decir,
	//se estara repitidiendo el sonido
	//hasta que le indiquemos lo contrario
	if (bActivo)
		FSOUND_SetLoopMode(iChannel, FSOUND_LOOP_NORMAL);
	//Si no desactivamos el loop
	else
		FSOUND_SetLoopMode(iChannel, FSOUND_LOOP_OFF);

}

//Pone en silencio el sonido
void CSound::SetSoundMute(bool bActivo)
{
	//El primer parametro es el numero de canal
	//al que queremos silenciar
	//El segundo parametro es bActivo
	//si es true activamos el silencio al sonido
	//si no le quitamos el silencio al sonido
	FSOUND_SetMute(iChannel, bActivo);
}

//Realiza un paneo al sonido
//debe estar entre 0 y 255
void CSound::SetSoundPanning(int iPan)
{
	//El primer parametro es el numero de canal
	//al que queremos hacer un paneo al sonido
	//El segundo parametro es el nuevo valor de
	//paneo puede estar entre 0 y 255. Si esta
	//a 0 es completamente a la izquierda o si
	//es 255 esta completamente a la derecha
	FSOUND_SetPan(iChannel, iPan);
}

//Pone uno de los canales del sonido 
//en efecto surround
void CSound::SetSoundSurround(bool bActivo)
{
	//El primer parametro es el numero de canal
	//al que queremos poner en estado surround
	//El segundo parametro es bActivo si es true
	//activamos el efecto surround de lo contario
	//lo desactivamos este efecto al sonido
	FSOUND_SetSurround(iChannel, bActivo);
}

//Devuelve 1 si se encuentra en loop
//el sonido ó 0 si no lo esta
int CSound::GetSoundLoop()
{
	return FSOUND_GetLoopMode(iChannel);
}
//Devuelve 1 si se encuentra en silencio
//el sonido ó 0 si no lo esta
int CSound::GetSoundMute()
{
	return FSOUND_GetMute(iChannel);
}

//Devuelve 1 si esta en pausa el
//sonido ó 0 si no esta en pausa
int CSound::GetSoundPaused()
{
	return FSOUND_GetPaused(iChannel);
}

//Devuelve el volumen actual
//Debe estar entre 0 y 255
int CSound::GetSoundVolume()
{
	return FSOUND_GetVolume(iChannel);

}
//Devuelve 1 si esta en estado de
//surround ó 0 si no esta en ese
//estado
int CSound::GetSoundSurround()
{
	return FSOUND_GetSurround(iChannel);
}

//Devuelve la posicion de paneo.
//Los siguientes valores son retornados:
//0 a la izquierda 
//128 a la mitad 
//255 a la derecha
int CSound::GetSoundPanning()
{
	return FSOUND_GetPan(iChannel);
}
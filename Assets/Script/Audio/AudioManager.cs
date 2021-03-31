
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using UnityEngine.UI;


public class AudioManager : MonoBehaviour
{
    JsonManager<AudioData> JM = new JsonManager<AudioData>("GameSoundData.json");
    AudioData data;

    [Header("Audio Controle")]
    public Scrollbar music;
    public Scrollbar sound;

    [Header("Audio Sources")]
    private Transform bgm;
    private Transform sounds;
    private Transform player;
    private readonly int hashVolume = Animator.StringToHash("volume");

    private void OnEnable()
    {
        data = new AudioData();
        JM.Load(ref data);
        music.value = data.music_volum;
        sound.value = data.sound_volum;

        bgm = transform.Find("bgm");
        sounds = transform.Find("sounds");
        player = GameObject.FindGameObjectWithTag("Player").transform;
    }
    private void Start()
    {
        SetAudioVolume(bgm, music.value);
        SetAudioVolume(sounds, sound.value);
        SetAnimationToAudioVolume(sounds, sound.value);
    }

    private void Update()
    {
        if(SetBgm() || SetSound()) JM.Save(data);
    }
    
    private void SetAudioVolume(Transform gameObject, float volume)
    {
        foreach (AudioSource audio in gameObject.GetComponentsInChildren<AudioSource>())
        {
            audio.volume = volume;
        }
    }
    private void SetAnimationToAudioVolume(Transform gameObject, float volume)
    {
        player.GetComponentInChildren<Animator>().SetFloat(hashVolume, volume);
        foreach (Animator animator in gameObject.GetComponentsInChildren<Animator>())
        {
            animator.SetFloat(hashVolume, volume);
        }
    }
    private bool SetBgm() // BackgoundMusic
    {
        if (data.music_volum == music.value) return false;
        data.music_volum = music.value;
        SetAudioVolume(bgm, music.value);
        return true;
    }
    private bool SetSound()
    {
        if (data.sound_volum == sound.value) return false;
        data.sound_volum = sound.value;
        SetAudioVolume(sounds, sound.value);
        SetAnimationToAudioVolume(sounds, sound.value);
        return true;
    }
    
    public void Play(List<AudioSource> audioList, string playType)
    {
        foreach (AudioSource audio in audioList)
        {
            if (audio.name.Equals(playType)) audio.Play();
        }
    }
}

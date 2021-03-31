
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public struct AudioData
{
    [SerializeField]
    public float music_volum;
    public float sound_volum;
}


public class Audio : MonoBehaviour
{
    public List<AudioSource> clips;

    private void OnEnable()
    {
        clips = new List<AudioSource>();
        for (int i = 0; i < transform.childCount; i++)
            clips.Add(transform.GetChild(i).GetComponent<AudioSource>());
    }
}

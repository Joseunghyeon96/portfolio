
using UnityEngine;

public class PlayerAudioSources : Audio
{
    #region Sigleton
    private static PlayerAudioSources instance;
    public static PlayerAudioSources Instance
    {
        get
        {
            if (instance == null)
                instance = FindObjectOfType<PlayerAudioSources>();
            return instance;
        }
    }
    #endregion

    public enum State
    {
        NULL = -1,
        ATTACK = 0,
        DEATH,
        PICKUPWEAPON,
        PUTDOWNWEAPON,
        WIRESHOOT,
        COUNT
    }

    public void Play(State state)
    {
        clips[(int)state].Play();
    }
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AudioToAnimation : StateMachineBehaviour
{
    public AudioClip clip;
    // OnStateEnter is called when a transition starts and the state machine starts to evaluate this state
    override public void OnStateEnter(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)
    {
        AudioSource.PlayClipAtPoint(clip, animator.transform.position, animator.GetFloat("volume"));
    }
}

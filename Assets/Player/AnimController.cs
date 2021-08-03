using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AnimController : MonoBehaviour
{
    Animator animator;
    CharacterController CC;
    // Start is called before the first frame update
    void Start()
    {
        animator = GetComponent<Animator>();
        CC = this.transform.parent.GetComponent<CharacterController>();
    }

    // Update is called once per frame
    void Update()
    {

        if(CC)
        animator.SetFloat("Speed", CC.velocity.magnitude, 0.1f, Time.deltaTime);
    }
}

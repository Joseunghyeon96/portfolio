/*
 *  Author: ariel oliveira [o.arielg@gmail.com]
 */

using UnityEngine;
using UnityEngine.UI;

public class PlayerStats : Stat
{
    #region Sigleton
    private static PlayerStats instance;
    public static PlayerStats Instance
    {
        get
        {
            if (instance == null)
                instance = FindObjectOfType<PlayerStats>();
            return instance;
        }
    }
    #endregion

    private Animator animator;

    void Awake()
    {
        animator = GetComponentInChildren<Animator>();
        isAlive = true;
        maxTotalHealth = 5;
        maxHealth = 100;
        health = maxHealth;
    }

    void Update()
    {
        Dead();
    }

    public override void Dead()
    {
        if (isAlive && health <= 0)
        {
            PlayerAudioSources.Instance.Play(PlayerAudioSources.State.DEATH);
            animator.Play("Death");
            isAlive = false;
            LoadSceneEvent.Instance.ShowCursor();
            Counter.Instance.SetGameState("GameOver");
        }
    }

    public bool isAttack()
    {
        return animator.GetCurrentAnimatorStateInfo(0).IsName("Attack");
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.tag.Equals("Monster")) Debug.Log("[OnTriggerEnter][" + other.gameObject.name+"]"+ other.gameObject.GetComponent<EnemyAI>().state);
    }

    private void OnCollisionEnter(Collision other)
    {
        if (other.gameObject.tag.Equals("Monster")) Debug.Log("[OnCollisionEnter][" + other.gameObject.name + "]" + other.gameObject.GetComponent<EnemyAI>().state);
    }
}

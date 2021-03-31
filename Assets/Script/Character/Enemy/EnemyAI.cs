using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyAI : MonoBehaviour
{
    public enum State
    {
        PATROL,
        TRACE,
        ATTACK,
        DIE
    }

    public State state = State.PATROL;

    private Transform player;
    private Transform enemy;

    private EnemyStat enemyStat;
    private Animator animator;

    public float attackDis = 2.0f;
    public float traceDis = 8.0f;

    private MoveAgent moveAgent;

    private readonly int hashMove = Animator.StringToHash("isMove");
    private readonly int hashAtk = Animator.StringToHash("isAtk");
    private readonly int hashSpeed = Animator.StringToHash("speed");
    private readonly int hashDie = Animator.StringToHash("Die");

    private void Awake()
    {
        player = GameObject.FindGameObjectWithTag("Player").GetComponent<Transform>();
        enemy = GetComponent<Transform>();
        moveAgent = GetComponent<MoveAgent>();
        animator = GetComponent<Animator>();
    } 

    private void OnEnable()
    {
        enemyStat = GetComponent<EnemyStat>();
        StartCoroutine(CheckState());
        StartCoroutine(Action());
    }

    IEnumerator Action()
    {
        while(enemyStat.isAlive)
        {
            yield return new WaitForSeconds(0.3f);
            switch(state)
            {
                case State.PATROL:
                    moveAgent.patrolling = true;
                    moveAgent.tracing = false;
                    animator.SetBool(hashAtk, false);
                    animator.SetBool(hashMove, true);
                    break;

                case State.TRACE:
                    moveAgent.patrolling = false;
                    moveAgent.tracing = true;
                    moveAgent.traceTarget = player.position;
                    animator.SetBool(hashAtk, false);
                    animator.SetBool(hashMove, true);
                    break;

                case State.ATTACK:
                    moveAgent.Stop();
                    animator.SetBool(hashMove, false);
                    animator.SetBool(hashAtk, true);
                    break;

                case State.DIE:
                    moveAgent.Stop();
                    animator.SetBool(hashMove, false);
                    animator.SetBool(hashAtk, false);
                    animator.SetTrigger(hashDie);
                    Counter.Instance.count -= 1;
                    enemyStat.Dead();
                    break;
            }
        }
    }

    IEnumerator CheckState()
    {
        while(enemyStat.isAlive)
        {
            if (state == State.DIE) yield break;

            float dis = Vector3.Distance(player.position, enemy.position);

            if (dis <= attackDis) state = State.ATTACK;
            else if (dis <= traceDis) state = State.TRACE;
            else state = State.PATROL;

            yield return new WaitForSeconds(0.3f);
        }
    }

    private void Update()
    {
        animator.SetFloat(hashSpeed, moveAgent.speed);
    }


    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag.Equals("Item"))
        {
            if (PlayerStats.Instance.isAttack()) state = State.DIE;
        }
    }
}

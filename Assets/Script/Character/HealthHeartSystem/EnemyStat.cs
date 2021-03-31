
using UnityEngine;

public class EnemyStat : Stat
{
    public int damage;
    private Animator anim;
    private float invincible_Time;   //무적 시간

    private void Awake()
    {
        anim = GetComponent<Animator>();

        isAlive = true;
        maxHealth = 100;
        health = maxHealth;

        invincible_Time = 0.0f;
    }

    void Update()
    {
        CooltimeManager();
        if (!isAlive) Destroy(this.gameObject, 2.0f);
    }
    
    public override void Dead()
    {
        isAlive = false;
    }

    public void CooltimeManager()
    {
        if (invincible_Time > 0.0f) invincible_Time -= Time.deltaTime;
    }
    private void OnTriggerEnter(Collider other)
    {
        // 조건 : 대상이 플레이어, 몬스터의 상태가 공격 상태, 플레이어의 무적 시간이 아닐 때
        if (other.gameObject.tag.Equals("Player"))
        {
            if (anim.GetCurrentAnimatorStateInfo(0).IsName("Attack") && invincible_Time <= 0.0f)
            {
                PlayerStats.Instance.TakeDamage(damage);
                invincible_Time = 1.0f;
            }
        }
    }
}

using UnityEngine;

public class Stat : MonoBehaviour
{
    public bool isAlive = true;

    public float health;
    public float maxHealth;
    protected float maxTotalHealth;

    public float Health { get { return health; } }
    public float MaxHealth { get { return maxHealth; } }
    public float MaxTotalHealth { get { return maxTotalHealth; } }

    public delegate void OnHealthChangedDelegate();
    public OnHealthChangedDelegate onHealthChangedCallback;


    public virtual void Heal(float health)
    {
        this.health += health;
        ClampHealth();
    }

    public virtual void TakeDamage(float dmg)
    {
        health -= dmg;
        ClampHealth();
    }
    
    public virtual void AddHealth()
    {
        if (maxHealth < maxTotalHealth)
        {
            maxHealth += 1;
            health = maxHealth;

            if (onHealthChangedCallback != null)
                onHealthChangedCallback.Invoke();
        }
    }

    public virtual void Dead()
    {
        if (health <= 0) isAlive = false;
    }

    void ClampHealth()
    {
        health = Mathf.Clamp(health, 0, maxHealth);

        if (onHealthChangedCallback != null)
            onHealthChangedCallback.Invoke();
    }
}

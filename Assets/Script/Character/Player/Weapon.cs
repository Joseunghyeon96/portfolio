using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Weapon : MonoBehaviour
{
    // 무기의 파라미터
    int durability;     // 내구도
    int damage;
    
    Player player;
    public bool hitAble;



    // Start is called before the first frame update
    void Start()
    {
        hitAble = false;
        player = GameObject.Find("Player").GetComponent<Player>();

        // 빛의 검
        if(gameObject.name == "Sword1")
        {
            durability = 10;
            damage = 30;
        }
        // 암흑 검
        else if (gameObject.name == "Sword2")
        {
            durability = 10;
            damage = 20;
        }
        // 일반 검
        else if (gameObject.name == "Sword3")
        {
            durability = 4;
            damage = 10;
        }
        // 닭
        else if (gameObject.name == "Sword4")
        {
            durability = 1;
            damage = 50;
        }
        // 관짝
        else if (gameObject.name == "Sword5")
        {
            durability = 5;
            damage = 20;
        }
        // 마법사
        else if (gameObject.name == "Sword6")
        {
            durability = 3;
            damage = 10;
        }
    }

    // Update is called once per frame
    void Update()
    {
        if(durability <= 0)
        {
            player.getItemParent = null;
            Destroy(gameObject);
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag.Equals("Monster") && hitAble)
        {
            durability--;
            hitAble = false;
        }
    }
}

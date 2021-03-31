using System.Collections;
using System.Collections.Generic;
using UnityEngine;


[System.Serializable]
public struct Monster
{
    [SerializeField]
    public GameObject prefab;
    public Vector2 count;
}

public class Spawner: MonoBehaviour
{
    public GameObject spawnPoints;
    private List<Transform> spawnPoint;
    public List<Monster> mosterPrefab;
    private List<GameObject> monsters;
    
    private void Awake()
    {
        spawnPoint = new List<Transform>();
        monsters = new List<GameObject>();
        for (int i = 0; i < spawnPoints.transform.childCount; i++)
        {
            spawnPoint.Add(spawnPoints.transform.GetChild(i));
        }
        Spawn();
    }
    
    private void Spawn()
    {
        foreach (Transform transform in spawnPoint) {

            Monster monster = mosterPrefab[(int)Random.Range(0, mosterPrefab.Count)];
            int monsterCount = (int)Random.Range(monster.count.x, monster.count.y + 1);
            for(int i = 0; i<monsterCount; i++)
            {
                GameObject go = Instantiate(monster.prefab, transform.position, Quaternion.identity, this.transform);
                monsters.Add(go);
            }
        }
    }
}

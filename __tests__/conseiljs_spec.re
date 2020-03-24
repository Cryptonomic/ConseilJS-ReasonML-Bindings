open Jest;

open ConseiljsRe;
open ConseiljsType;
 /* let () =
   describe(
     "ConseilQueryBuilder",
     ExpectJs.(
       () => {
         test("#blankQuery", () => {
           let query = ConseilQueryBuilder.blankQuery();
           expect(query##limit) |> toBe(100);
         });
         test("#addFields", () => {
           let query = ConseilQueryBuilder.blankQuery();
           let entities = ["block_hash", "operation_group_hash", "kind", "source", "destination", "amount", "fee", "slots"];
           let newQuery = ConseilQueryBuilder.addFields(query, entities);
           Js.log("addFields");
           Js.log(newQuery##limit);
           expect(newQuery##limit) |> toBe(100);
         });
         test("#addPredicate", () => {
           let query = ConseilQueryBuilder.blankQuery();
           let query = ConseilQueryBuilder.addPredicate(query, "block_hash", ConseiljsType.EQ, [|`Str("test")|], false);
           expect(query##limit) |> toBe(100);
         });
         test("#addOrdering", () => {
           let query = ConseilQueryBuilder.blankQuery();
           let query = ConseilQueryBuilder.addOrdering(query, "block_level", ConseiljsType.DESC);
           Js.log("addOrdering");
           Js.log(query##orderBy[0]##field);
           expect(query##orderBy[0]##field) |> toBe("block_level");
         });
         test("#setLimit", () => {
           let query = ConseilQueryBuilder.blankQuery();
           let query = ConseilQueryBuilder.setLimit(query, 1);
           Js.log("setLimit");
           Js.log(query##limit);
           expect(query##limit) |> toBe(1);
         });
         test("#addAggregationFunction", () => {
           let query = ConseilQueryBuilder.blankQuery();
           let entities = ["block_hash", "operation_group_hash", "kind", "source", "destination", "amount", "fee", "slots"];
           let query = ConseilQueryBuilder.addFields(query, entities);
           let query = ConseilQueryBuilder.addAggregationFunction(query, "fee", ConseiljsType.SUM);
           expect(query##aggregation[0]##field) |> toBe("fee");
         });

       }
     ),
   ); */

   /* let () =
   describe(
     "TezosConseilClient",
     ExpectJs.(
       () => {
         test("#getTezosEntityData", () => {
           let query = ConseilQueryBuilder.blankQuery();
           let entities = ["block_hash", "operation_group_hash", "kind", "source", "destination", "amount", "fee", "slots"];
           let query = ConseilQueryBuilder.addFields(query, entities);
           let query = ConseilQueryBuilder.addAggregationFunction(query, "fee", ConseiljsType.SUM);
           expect(query##aggregation[0]##field) |> toBe("fee");
         });
         test("#getBlock", () => {
           let blockid = "BLBiMfnsKAwfzdmUoq3QKpZijiPFNf36n6GD96HbvMPCNWZHHQQ"; 
           let query = ConseilQueryBuilder.blankQuery();
           let entities = ["block_hash", "amount", "fee"];
           let query = ConseilQueryBuilder.addFields(query, entities);
           let query = ConseilQueryBuilder.addPredicate(query, "block_hash", ConseiljsType.EQ, [|blockid|], false);
           let query = ConseilQueryBuilder.addAggregationFunction(query, "fee", ConseiljsType.SUM);
           let query = ConseilQueryBuilder.addAggregationFunction(query, "amount", ConseiljsType.SUM);
           let blockPromise = TezosConseilClient.getBlock(conseilServerInfo, network, blockid);
           let aaa = Js.Promise.(
            blockPromise
             |> then_(values => {
               Js.log("blockPromise");
               Js.log(values);
               resolve(values);
             })
           );
           expect(query##limit) |> toBe(100);
         });

       }
     ),
   ); */